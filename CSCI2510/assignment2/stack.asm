.386
.model flat, stdcall
option casemap:none
include windows.inc
include kernel32.inc
include msvcrt.inc
includelib msvcrt.lib
includelib ucrtd.lib

.data
inputStatement db "Enter NUMBER or FUNCTION:", 10, "(any positive number: the number to be pushed onto the top of stack;", 10, " 0: pop the number from the top of the stack;" , 10 ,"-1: print out the number on the top of the stack without popping it;", 10, "-2: print out the size of numbers that have been pushed into the stack;",10, "-3: print out the contents of the stack.)", 10,  0
numberFormat db "%d", 0 ; format for scan
stackFormat1 db "===stack status===", 10, 0 ;format for print stack status
stackFormat2 db "      |%4d|      ", 10, 0 ;format for print stack status
stackFormat3 db "      ------      ", 10, 0 ;format for print stack status
stackFormat4 db "==================", 10, 0 ;format for print stack status
outputFormatForPop db "Pop %d", 10, 0 ; format for pop
outputFormatForTop db "Stack top is %d", 10, 0 ; format for gettopnumber
outputFormatForPrintIsEmpty db "Stack is empty", 10, 0; format for top when stack is empty
outputFormatForPrintSize db "Current stack size is %d", 10, 0; format for getsize
pushErrorStatement db "ERROR THE STACK IS FULL", 10, 0 ; error statement
popErrorStatement db "ERROR THE STACK IS EMPTY", 10, 0 ; error statement

stack dword 10 dup(1) ; Memory allocation for stack
stacklength dword 10 ; stack length
inputnumber dword "%d" ; hold the input number

.code
start:
	mov EBP, 4 ; make top pointer be equal to largest address of the stack, then store the largest address into EBP
	imul EBP, stacklength
	add EBP, offset stack

	jmp input ; jmp to input

input:
	invoke crt_printf, addr inputStatement 
	invoke crt_scanf, addr numberFormat, addr inputnumber ; input number
	mov ECX, inputnumber ; load the inputnumber in ECX

	cmp ECX, 0; compare content of ECX with 0 (Exercise 1)
	je popnum; if content of ECX is equal to 0, then jump to popnum (Exercise 1)

	;(Exercise 3)
	cmp ECX, -1; compare content of ECX with -1
	je gettop; if content of ECX is equal to -1, then jump to gettop

	cmp ECX, -2; compare content of ECX with -2
	je getsize; if content of ECX is equal to -2, then jump to getsize
	;(Exercise 3)
	
	cmp ECX, -3; compare content of ECX with -3
	je showstack ; jump to print out the contents of the stack.
	jmp pushnum; jump to pushnum

pushnum:
	;(Exercise 2)
	mov EBX, offset stack ; make EBX be equal to smallest address of the stack
	cmp EBP, EBX; compare content of EBP with EBX 
	je pusherror; if content of EBP is equal to EBX, it means EBP is pointing to the smallest address of the stack, 
	;			  it means the stack is full, then jump to pusherror
	;(Exercise 2)

	sub EBP, 4; decrease the top pointer by 4 (Exercise 1)
	mov [EBP], ECX; push the inputnumber into stack in memory (Exercise 1)
	jmp input

popnum:
	;(Exercise 2)
	mov EBX, 4 ; make EBX be equal to largest address of the stack
	imul EBX, stacklength
	add EBX, offset stack
	cmp EBP, EBX; compare content of EBP with EBX
	je poperror; if content of EBP is equal to EBX, it means EBP is pointing to the largest address of the stack, 
	;			 it means the stack is empty, then jump to poperror
	;(Exercise 2)

	mov ECX, [EBP]; get the top data of in the stack in memory, and load it to ECX (Exercise 1)
	invoke crt_printf, addr outputFormatForPop, ECX ; print out the top data
	add EBP, 4; increase the top pointer by 4 (Exercise 1)
	jmp input
	
showstack:
	invoke crt_printf, addr stackFormat1
	mov EBX, EBP
	jmp showstackdata

showstackdata:
	mov EAX, 4
	imul EAX, stacklength
	add EAX, offset stack ; compute the largest memory address of stack
	cmp EBX, EAX; see if the iterater is end
	je showstackend
	mov ECX, [EBX] ; mov the data to ECX
	invoke crt_printf, addr stackFormat2, ECX ; print out the data
	invoke crt_printf, addr stackFormat3 
	add EBX, 4 ; increase the pointer
	jmp showstackdata

showstackend:
	invoke crt_printf, addr stackFormat4
	jmp input

pusherror:
	invoke crt_printf, addr pushErrorStatement ; print push error message
	jmp exitprogram

poperror:
	invoke crt_printf, addr popErrorStatement ; print pop error message
	jmp exitprogram

;(Exercise 3)
gettop:
	mov EBX, 4 ; make EBX be equal to largest address of the stack
	imul EBX, stacklength
	add EBX, offset stack
	cmp EBP, EBX; compare content of EBP with EBX
	je isempty; if content of EBP is equal to EBX, it means EBP is pointing to the largest address of the stack, 
	;			it means the stack is empty, then jump to isempty

	mov ECX, [EBP]; get the top data of in the stack in memory, and load it to ECX
	invoke crt_printf, addr outputFormatForTop, ECX ; print out the top data
	jmp input

getsize:
	; AS: (EBX-EBP)/4 = size
	mov EBX, 4 ; make EBX be equal to largest address of the stack
	imul EBX, stacklength
	add EBX, offset stack
	sub EBX, EBP

	; We perform division here
	mov EAX, EBX
	mov EBX, 4
	mov EDX, 0
	idiv EBX
	; EAX becomes quoient, EDX becomes remainder
	; Then EAX will be the size of the stack
	invoke crt_printf, addr outputFormatForPrintSize, EAX; print info that the size of the stack
	jmp input
;(Exercise 3)

isempty:
	invoke crt_printf, addr outputFormatForPrintIsEmpty ; print info that the stack is empty
	jmp input

exitprogram:
	invoke ExitProcess, NULL

end start
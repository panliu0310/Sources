.386
.model flat, stdcall
option casemap:none
include windows.inc
include kernel32.inc
include msvcrt.inc
includelib msvcrt.lib
includelib ucrtd.lib

.data
InputStatement db "Memory Address Access(input positive number < 65536): ", 0
MemoryAddressFormat  db "%d", 0
MemoryAddress dd "%d", 0
OutputFormat1 db "cache tag status: ", 0
OutputFormat2 db "%d ", 0
OutputFormat3 db 10 , 0
OutputCacheHit db "Cache Hit!", 10, 0

CacheSize dd 4, 0 ; Number of cache blocks
CacheTags dd 4 dup(-1) ; Each cache block is associated with a tag 
;CacheBlocks dd 4 dup (-1) ; Please note that a cache should contain tags and 
						    ; data block, but we don't use blocks here for simplicity
CacheTimes dd 4 dup(-1)

WordSize db 1, 0 ; Suppose this value is k. It means that the size of a word is 2^k bytes
BlockSize db 4, 0 ; Suppose this value is n. It means that the size of a block is 2^n bytes

CurrentTimeStamp dd 0 ; Store the current time stamp

.code
start:
	mov EBP, offset CacheTags
	mov ESI, offset CacheTimes
	jmp input

input:
	mov EAX, CurrentTimeStamp
	inc EAX
	mov CurrentTimeStamp, EAX
	invoke crt_printf, addr InputStatement
	invoke crt_scanf, addr MemoryAddressFormat, addr MemoryAddress
	mov EAX, MemoryAddress ; EAX stores the input
	cmp EAX, -1
	je ExitProgram
	jmp SearchCache

SearchCache:    ; EAX stores the memory address
	mov CL, BlockSize ; CL is the lowest 8-bit in the ECX 
	shr EAX, CL ; EAX stores the corresponding tag ID of the input memory addr
				; If we want to shift arbitrary number of bits,  
				; the value has to be imm8 or be stored inside the CL
	mov ECX, 0  ; Treat ECX as counter
SearchNextCB:
	cmp EAX, [EBP + 4*ECX] ; compare whether the tag
	je CacheHit 
	inc ECX 
	cmp ECX, CacheSize ; check whether all CacheTags are searched
	jne SearchNextCB
	jmp CacheMiss
	
CacheHit: ; Handle the cache hit
	mov EAX, CurrentTimeStamp
	mov [ESI + 4*ECX], EAX ; Update the time stamp
	invoke crt_printf, addr OutputCacheHit ; Print out "Cache Hit!"
	jmp PrintCacheStatus

CacheMiss: ; Handle the cache miss
	; We implement LRU here to choose the block to be replaced
	; Step1: Use LRU to find the smallest time stamp block
	; Step2: Do the replacement
	; EAX stores the new tag now
	mov ECX, 0
	mov EBX, ECX ; EBX record the index to the smallest time stamp
	mov EDX, [ESI + 4*ECX] ; EDX store the first time stamp
my_repeat:
	inc ECX
	cmp ECX, CacheSize ; check whether all time stamps are searched
	je done
	cmp EDX, [ESI + 4*ECX]
	jle my_repeat ; jump if EDX is still the smallest the time stamp
	mov EDX, [ESI + 4*ECX] ; Update the EDX to the smallest time stamp
	mov EBX, ECX ; EBX record the index to the smallest time stamp
	jmp my_repeat
done: 
	mov [EBP + 4*EBX], EAX ; update the tag
	mov EDX, CurrentTimeStamp ; load the current time stamp 
	mov [ESI + 4*EBX], EDX ; update the time stamp 
	jmp PrintCacheStatus

PrintCacheStatus: ; Print all the tags in the CacheTags
	invoke crt_printf, addr OutputFormat1
	mov EBX, 0
RepeatPrint:
	mov EAX, [EBP + 4*EBX] ; move the corresponding value in CacheTags into EBX 
	invoke crt_printf, addr OutputFormat2, EAX ; print out the value
	inc EBX ; increase to the next Tag
	cmp EBX, CacheSize ; find out whether all tags are printed
	jne RepeatPrint ; if not, jump back to print the next tag
	invoke crt_printf, addr OutputFormat3 
	jmp input ; if yes, jump back to get the next memory address

ExitProgram:
	invoke ExitProcess, NULL

end start
.386
.model flat, stdcall
option casemap:none
include windows.inc
include kernel32.inc
include msvcrt.inc
includelib msvcrt.lib
includelib ucrtd.lib

.data
InputStatement db "Memory Address Access(input positive number or input -1:exit program): ", 0
MemoryAddressFormat  db "%d", 0
MemoryAddress dd "%d", 0
OutputFormat1 db "cache tag status: ", 0
OutputFormat2 db "%d ", 0
OutputFormat3 db 10 , 0

CacheSize dd 16, 0 ; Number of cache blocks
CacheTags dd 16 dup(-1) ; Each cache block is associated with a tag 
;CacheBlocks dd 16 dup (-1) ; Please note that a cache should contain tags and 
						    ; data block, but we don't use blocks here for simplicity

WordSize db 1, 0 ; Suppose this value is k. It means that the size of a word is 2^k bytes
BlockSize db 4, 0 ; Suppose this value is n. It means that the size of a block is 2^n bytes

.code
start:
	mov EBP, offset CacheTags
	jmp input

input:
	invoke crt_printf, addr InputStatement
	invoke crt_scanf, addr MemoryAddressFormat, addr MemoryAddress
	mov EAX, MemoryAddress ; EAX stores the input
	cmp EAX, -1
	je ExitProgram
	jmp SearchCache

SearchCache: ; EAX stores the memory address
	mov CL, BlockSize ; CL is the lowest 8-bit in the ECX 
	shr EAX, CL ; EAX stores the corresponding block ID of the input memory addr
				; If we want to shift arbitrary number of bits,  
				; the value has to be imm8 or be stored inside the CL
	mov EBX, EAX
	and EBX, 15 ; EBX stores the mapped Cache Block of the given block ID
	mov CL, 4   ; Because there are totally 16 cache blocks inside the Cache
				; the cache block IDs range from 0~15, so 4 bit is enough
	shr EAX, CL ; find out the tag of the given block ID
	cmp EAX, [EBP + 4*EBX] ; find out it's a hit or miss
	je PrintCacheStatus ; if hit, jump to PrintCacheStatus
	mov [EBP + 4*EBX], EAX ; if miss, move the new tag to the CacheTags
	jmp PrintCacheStatus ; jump to PrintCacheStatus

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
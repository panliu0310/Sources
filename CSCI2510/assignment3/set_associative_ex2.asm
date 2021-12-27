.386
.model flat, stdcall
option casemap:none
include windows.inc
include kernel32.inc
include msvcrt.inc
includelib msvcrt.lib
includelib ucrtd.lib

.data
InputStatement db "Memory Address Access(input a positive number < 65536): ", 0
MemoryAddressFormat  db "%d", 0
MemoryAddress dd "%d", 0
OutputFormat1 db "cache tag status: ", 0
OutputFormat2 db "%d ", 0
OutputFormat3 db 10 , 0
OutputFormat4 db "Accumulated Cache Hits: %d", 10, 0

CacheSize dd 128, 0 ; Number of total cache blocks
SetSize dd 4; Number of cache blocks in a set
CacheTags dd 128 dup(-1) ; Each cache block is associated with a tag 
;CacheBlocks dd 128 dup(-1) ; Please note that a cache should contain tags and 
						    ; data block, but we don't use blocks here for simplicity
CacheTimes dd 128 dup(-1)

BlockSize db 5, 0 ; Suppose this value is n. It means that the size of a block is 2^n bytes

CacheHits dd 0 ; Record the number of cache hits
CurrentTimeStamp dd 0 ; Record the current time stamp

.code
start:
	jmp input

input:
	mov EAX, CurrentTimeStamp 
	inc EAX
	mov CurrentTimeStamp, EAX ; update the time stamp
	mov EBP, offset CacheTags  ; Hint: EBP could be updated in the process, so initialize here
	mov ESI, offset CacheTimes ; Hint: ESI could be updated in the process, so initialize here
	invoke crt_printf, addr InputStatement
	invoke crt_scanf, addr MemoryAddressFormat, addr MemoryAddress
	mov EAX, MemoryAddress ; EAX stores the input, which is the requested memory address
	cmp EAX, -1
	je ExitProgram
	call SearchSets
	call SearchTags
	call CacheHit
	call CacheMiss
	jmp PrintCacheHits

SearchSets proc
	; Search which set is the input memory address being mapped to
	mov CL, BlockSize ; CL stores 5, since there are 2^4 words in a block and 2^1 bytes in a word
	shr EAX, CL ; EAX stores the corresponding memory block ID of the input memory addr
	mov EBX, EAX ; EBX now stores the tag and mapped set from the given address
	and EBX, 31 ; EBX now stores the mapped set from the given address
				; Why 31? because there are 128/4 = 32 sets
				; The value of EBX is from Set 0 to Set 31
SearchSets endp

SearchTags proc
	; Search all tags in the set to find out cache hit or miss
	shr EAX, 5 ; EAX stores the tag from the given address
			   ; The value of EAX is from Tag 0 to Tag 63
	shl EBX, 4 ; EBX now stores address of mapped set
	add EBP, EBX; Instead of pointing to offset CacheTags, EBP now points to the corresponding sets of CB
SearchTags endp

CacheHit proc
	; Handle the cache hit
	; Do something if there is a cache hit
	mov ECX, 0
	cmp EAX, [EBP] ; find out if it's a hit (with the 1st CB in the set)
	je PrintCacheHits
	cmp EAX, [EBP + 4] ; find out if it's a hit (with the 2nd CB in the set)
	je PrintCacheHits
	cmp EAX, [EBP + 8] ; find out if it's a hit (with the 3rd CB in the set)
	je PrintCacheHits
	cmp EAX, [EBP + 12] ; find out if it's a hit (with the 4th CB in the set)
	je PrintCacheHits
CacheHit endp

CacheMiss proc ; Handle the cache miss by FIFO replacement algorithm
	mov ECX, 0
	add ESI, EBX; Instead of pointing to offset CacheTimes, ESI now points to the corresponding sets of CB
	mov EBX, ECX ; EBX record the index to the smallest time stamp
	mov EDX, [ESI] ; EDX store the first time stamp
my_repeat:
	inc ECX
	cmp ECX, 4 ; check whether all time stamps are searched
	je done
	cmp EDX, [ESI + 4*ECX]
	jle my_repeat ; jump if EDX is still the smallest time stamp
	mov EDX, [ESI + 4*ECX] ; Update the EDX to the smallest time stamp
	mov EBX, ECX ; EBX record the index to the smallest time stamp
	jmp my_repeat
done: 
	mov [EBP + 4*EBX], EAX ; update the tag
	mov EDX, CurrentTimeStamp ; load the current time stamp 
	mov [ESI + 4*EBX], EDX ; update the time stamp 
	dec CacheHits
	jmp PrintCacheHits
CacheMiss endp

PrintCacheHits:
	; By doing the following, you can save the values in the registers
	inc CacheHits
	push EAX
	push EBX
	push ECX
	push EDX 
	mov EAX, CacheHits
	invoke crt_printf, addr OutputFormat4, EAX
	; By doing the following, you can restore the values in the registers
	pop EDX
	pop ECX
	pop EBX
	pop EAX
	jmp input

; This function will not be used during the testing
; But this function is preserved in case that you want to debug by using this
PrintCacheStatus: ; Print all the tags in the CacheTags
	mov EBP, offset CacheTags  ; Hint: EBP could be updated in the process, so initialize here
	mov ESI, offset CacheTimes ; Hint: ESI could be updated in the process, so initialize here
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
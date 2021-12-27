.386
.model flat, stdcall
option casemap:none
include windows.inc
include kernel32.inc
include msvcrt.inc
includelib msvcrt.lib
includelib ucrtd.lib
.data
MyName db "Name: Liu Hoi Pan", 13, 10, 0
MySID db "SID: 1155127464", 13, 10, 0
MyCollege db "College: Chung Chi", 13, 10, 0
MyMajor db "Major: Mathematics", 13, 10, 0
.code
start:
invoke crt_printf, addr MyName
invoke crt_printf, addr MySID
invoke crt_printf, addr MyCollege
invoke crt_printf, addr MyMajor
invoke ExitProcess, 0
end start
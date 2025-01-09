section .data
hello db  'Hello World!',10;'Hello World!' plus a linefeed 
helloLen equ $-hello ; Length of the 'Hello World!' string

section .text

global _start

_start:
mov eax,4
mov ebx,1
mov ecx,hello
mov edx,helloLen
int 80h

mov eax,1
xor ebx,ebx
int 80h

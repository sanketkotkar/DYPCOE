section .data
msg db 'The Largest Number is:', 0Ah, 0
len equ $ - msg
arr dd 1aaaaaa1h, 22h, 11h, 3abcdee3h, 444h

section .bss
count resb 1
result resb 12

section .text
global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, len
    int 80h

    mov byte [count], 5
    xor eax, eax
    mov esi, arr

loop1:
    cmp eax, [esi]
    jnc next
    mov eax, [esi]

next:
    add esi, 4
    dec byte [count]
    jnz loop1

    mov ebx, eax
    mov esi, result
    mov byte [count], 8

L1:
    mov dl, bl
    and dl, 0Fh
    cmp dl, 9
    jbe l2

    add dl, 37h
    jmp store

l2:
    add dl, 30h

store:
    mov [esi], dl
    inc esi
    rol ebx, 4
    dec byte [count]
    jnz L1

    mov byte [esi], 0Ah

    mov edx, 9
    mov ecx, result
    mov ebx, 1
    mov eax, 4
    int 80h

    mov eax, 1
    xor ebx, ebx
    int 80h

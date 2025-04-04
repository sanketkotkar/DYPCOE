section .data
newline db 0xa
num db 4
result db 0,0,0,0

section .text
global _start

_start:
    mov ax,1
    mov bh,0
    mov bl,[num]
    call fact

    mov esi,result ; convert to ascii and display
    mov cl,4 ; iter1 ax=78 iter2

up:
    rol ax,4 ; ax=87 ax = 78
    mov dx,ax ; dx = 87 dx=78
    and ax,0fh ; ax=07 ax=08
    cmp al,09
    jbe skip
    add al,07

skip:
    add al,30h
    mov [esi],al ; result[0]=37 result[1]=38
    inc esi ; result++
    mov ax,dx ; ax = 87 ax = 78
    dec cl ; cl= 3 cl = 2
    jnz up

    mov rax,1
    mov rdi,1
    mov rsi,result ; display string i.e. result= 78
    mov rdx,4
    syscall

    ; Print newline
    mov rax,1
    mov rdi,1
    mov rsi,newline
    mov rdx,1
    syscall
    mov rdx,4
    syscall

    mov rax,60
    mov rdi,0
    syscall

; procedure - recursive iteration 1 2 3 4
fact:
    cmp bx,1
    jne next
    ret

next:
    mul bx ; ax*bx ax =5 20 60 120
    dec bx ; bx = 4 3 2 1
    call fact
    ret

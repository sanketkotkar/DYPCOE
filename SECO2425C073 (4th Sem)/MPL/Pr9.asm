section .data
    sourceBlock db 12h, 45h, 87h, 24h, 97h
    count equ 5

    msg db "ALP for overlapped block transfer using string instructions:",10
    msg_len equ $-msg

    msgSource db 10,"The Source block contains the Elements:",10
    msgSource_len equ $-msgSource

    msgDest db 10,"The Destination block contains the Elements:",10
    msgDest_len equ $-msgDest

    bef db 10,"Before Block Transfer:",10
    beflen equ $-bef

    aft db 10,10,"After Block Transfer:",10
    aftlen equ $-aft

    space db 20h
    space_len equ $-space

    newline db 10
    newline_len equ $-newline

section .bss
    destBlock resb 5
    result resb 4

%macro write 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

section .text
    global _start

_start:
    write msg, msg_len
    write bef, beflen
    write msgSource, msgSource_len
    mov rsi, sourceBlock
    call dispBlock

    write msgDest, msgDest_len
    mov rsi, destBlock
    call dispBlock

    lea rsi, [sourceBlock + count - 1]
    lea rdi, [destBlock + count - 1]
    mov rcx, count
    std
    rep movsb
    cld

    write aft, aftlen
    write msgSource, msgSource_len
    mov rsi, sourceBlock
    call dispBlock

    write msgDest, msgDest_len
    mov rsi, destBlock
    call dispBlock

    mov rax, 60
    mov rdi, 0
    syscall

dispBlock:
    mov rbp, count
next:
    mov al, [rsi]
    push rsi
    call disp
    pop rsi
    inc rsi
    dec rbp
    jnz next

    write newline, newline_len
    ret

disp:
    mov bl, al
    mov rdi, result
    mov cx, 2

up1:
    rol bl, 4
    mov al, bl
    and al, 0fh
    cmp al, 9h
    jg add_37
    add al, 30h
    jmp skip1

add_37:
    add al, 37h

skip1:
    mov [rdi], al
    inc rdi
    dec cx
    jnz up1

    write result, 2
    write space, space_len
    ret


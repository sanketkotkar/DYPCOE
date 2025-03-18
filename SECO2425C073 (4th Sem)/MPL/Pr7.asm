Section .data
M1 db 10,'Sorry!!!Processor is in real Mode'
M1_len:equ $-M1

Pmodemsg db 10,'Processor is in Protected Mode'
Pmsg_len:equ $-Pmodemsg

Gdtmsg db 10,'GDTR Contents are::',10
Gmsg_len:equ $-Gdtmsg

Ldtmsg db 10,'LDTR Contents are::',10
Lmsg_len:equ $-Ldtmsg

Idtmsg db 10,'IDTR Contents are::',10
Imsg_len:equ $-Idtmsg

Mswmsg db 10,'Machine Status Word::',10
Mmsg_len:equ $-Mswmsg

Trmsg db 10,'Task Register::',10
Tmsg_len equ $-Trmsg

Colmsg db ':',10
Colmsg_len equ $-Colmsg

Nwline db 10
Nwline_len equ $-Nwline

Section .bss
Gdtr resb 6
Ldtr resb 2
Idtr resb 6
Msw resw 1
Tr resw 1
Dnum_buff resb 04

%macro disp 2
mov eax,04
mov ebx,01
mov ecx,%1
mov edx,%2
int 80h
%endmacro

section .text
global _start
_start:
smsw eax
bt eax,0
jc prmode
disp M1,M1_len
Jmp next1
prmode:disp Pmodemsg,Pmsg_len
next1: sgdt[Gdtr]
          sldt[Ldtr]
          sidt[Idtr]
          str[Tr]
          smsw ax
          mov [Msw],ax
          
          disp Gdtmsg,Gmsg_len
          mov bx,[Gdtr+4]
          call disp_num
          mov bx,[Gdtr+2]
          call disp_num
          disp Colmsg,Colmsg_len
          mov bx,[Gdtr]
          call disp_num
          
          disp Ldtmsg,Lmsg_len
          mov bx,[Ldtr]
          call disp_num
          
          disp Idtmsg,Imsg_len
          mov bx,[Idtr+4]
          call disp_num
          mov bx,[Idtr+2]
          call disp_num
          
          disp Colmsg,Colmsg_len
          mov bx,[Idtr]
          call disp_num
          
          disp Trmsg,Tmsg_len
          mov bx,[Tr]
          call disp_num
          
          disp Mswmsg,Mmsg_len
          mov bx,[Msw]
          call disp_num
          
Exit: 
disp Nwline,Nwline_len
mov eax,01
mov ebx,ebx
int 80h

disp_num:
          mov esi,Dnum_buff
          mov ecx,04
          up1:
            rol bx,04
            mov dl,bl
            and dl,0fh
            add dl,'0'
            cmp dl,'9'
            jbe skip1
            add dl,07h
skip1:
mov [esi],dl
inc esi
loop up1
disp Dnum_buff,4
ret

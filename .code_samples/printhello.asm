[org 0x7c00]

call say_hello

jmp $

say_hello:
pusha
mov ah, 0x0e
mov al, 'H'
int 0x10
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
mov al, 'l'
int 0x10
mov al, 'o'
int 0x10
mov al, ' '
int 0x10
mov al, 'F'
int 0x10
mov al, 'O'
int 0x10
mov al, 'O'
int 0x10

;mov ah, 0x0
;int 0x16

;mov ah, 0x0e
;int 0x10

popa
ret


times 510-($-$$) db 0

dw 0xaa55

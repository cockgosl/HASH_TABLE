global my_strcmp

section .text

my_strcmp:
        movzx eax, byte [rdi]
        movzx ebx, byte [rsi]

.loop:
        cmp eax, ebx
        jne .diff

        test eax, eax
        je .equal

        inc rdi
        inc rsi
        jmp .loop

.diff:
        sub eax, ebx
        ret
.equal:
        xor eax, eax
        ret

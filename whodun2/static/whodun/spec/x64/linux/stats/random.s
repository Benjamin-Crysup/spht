
.text
.globl	whodun_Random_drawFloat_help_norm
.type	whodun_Random_drawFloat_help_norm, @function

/*
rdi = num
rsi = dst
*/

whodun_Random_drawFloat_help_norm:
	endbr64
	leaq whodun_Random_drawFloat_help_norm_oneF(%rip), %rax
	movsd (%rax), %xmm1
	movq $0x000FFFFFFFFFFFFF, %r8
	movq $0x3FF0000000000000, %r9
	whodun_Random_drawFloat_help_norm_again:
	movq (%rsi), %rax
	andq %r8, %rax
	orq %r9, %rax
	movq %rax, (%rsi)
	movsd (%rsi), %xmm0
	subsd %xmm1, %xmm0
	movsd %xmm0, (%rsi)
	addq $8, %rsi
	decq %rdi
	jnz whodun_Random_drawFloat_help_norm_again
	ret

.align 8
whodun_Random_drawFloat_help_norm_oneF:
.double 1.0


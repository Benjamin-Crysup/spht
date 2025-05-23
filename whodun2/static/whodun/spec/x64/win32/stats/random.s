
.text
.globl	whodun_Random_drawFloat_help_norm

/*
rcx = num
rdx = dst
*/

whodun_Random_drawFloat_help_norm:
	endbr64
	leaq whodun_Random_drawFloat_help_norm_oneF(%rip), %rax
	movsd (%rax), %xmm1
	movq $0x000FFFFFFFFFFFFF, %r8
	movq $0x3FF0000000000000, %r9
	whodun_Random_drawFloat_help_norm_again:
	movq (%rdx), %rax
	andq %r8, %rax
	orq %r9, %rax
	movq %rax, (%rdx)
	movsd (%rdx), %xmm0
	subsd %xmm1, %xmm0
	movsd %xmm0, (%rdx)
	addq $8, %rdx
	decq %rcx
	jnz whodun_Random_drawFloat_help_norm_again
	ret

.align 8
whodun_Random_drawFloat_help_norm_oneF:
.double 1.0


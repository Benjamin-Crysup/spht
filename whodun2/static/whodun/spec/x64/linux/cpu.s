
.text
.globl	whodun_packPtr_imp
.type	whodun_packPtr_imp, @function
.globl	whodun_unpackPtr_imp
.type	whodun_unpackPtr_imp, @function

whodun_packPtr_imp:
whodun_unpackPtr_imp:
	endbr64
	movq %rdi, %rax
	ret

.globl	whodun_packFlt_imp
.type	whodun_packFlt_imp, @function

whodun_packFlt_imp:
	endbr64
	subq $8, %rsp
	movsd %xmm0, (%rsp)
	movq (%rsp), %rax
	addq $8, %rsp
	ret

.globl	whodun_unpackFlt_imp
.type	whodun_unpackFlt_imp, @function

whodun_unpackFlt_imp:
	endbr64
	subq $8, %rsp
	movq %rdi, (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	ret

/*TODO check cmpq*/

.globl	whodun_min_imp
.type	whodun_min_imp, @function

whodun_min_imp:
	endbr64
	movq %rdi, %rax
	cmpq %rsi, %rdi
	cmovg %rsi, %rax
	ret

.globl	whodun_max_imp
.type	whodun_max_imp, @function

whodun_max_imp:
	endbr64
	movq %rsi, %rax
	cmpq %rsi, %rdi
	cmovg %rdi, %rax
	ret

.globl	whodun_umin_imp
.type	whodun_umin_imp, @function

whodun_umin_imp:
	endbr64
	movq %rdi, %rax
	cmpq %rsi, %rdi
	cmova %rsi, %rax
	ret

.globl	whodun_umax_imp
.type	whodun_umax_imp, @function

whodun_umax_imp:
	endbr64
	movq %rsi, %rax
	cmpq %rsi, %rdi
	cmova %rdi, %rax
	ret

.globl	whodun_fmin_imp
.type	whodun_fmin_imp, @function

whodun_fmin_imp:
	endbr64
	/*Test a for nan*/
		ucomisd %xmm0, %xmm0
		jp whodun_fmin_imp_awins
	/*Test for a clear winner*/
		ucomisd %xmm1, %xmm0
		jp whodun_fmin_imp_bwins
		ja whodun_fmin_imp_bwins
		jb whodun_fmin_imp_awins
	/*Float equal, test if B is +0*/
		subq $8, %rsp
		movsd %xmm1, (%rsp)
		movq (%rsp), %rax
		addq $8, %rsp
		cmpq $0, %rax
		jz whodun_fmin_imp_awins
	/*Either, so let b win*/
	whodun_fmin_imp_bwins:
		movsd %xmm1, %xmm0
	whodun_fmin_imp_awins:
	ret

.globl	whodun_fmax_imp
.type	whodun_fmax_imp, @function

whodun_fmax_imp:
	endbr64
	/*Test a for nan*/
		ucomisd %xmm0, %xmm0
		jp whodun_fmax_imp_awins
	/*Test for a clear winner*/
		ucomisd %xmm1, %xmm0
		jp whodun_fmax_imp_bwins
		jb whodun_fmax_imp_bwins
		ja whodun_fmax_imp_awins
	/*Float equal, test if A is +0*/
		subq $8, %rsp
		movsd %xmm0, (%rsp)
		movq (%rsp), %rax
		addq $8, %rsp
		cmpq $0, %rax
		jz whodun_fmax_imp_awins
	/*Either, so let b win*/
	whodun_fmax_imp_bwins:
		movsd %xmm1, %xmm0
	whodun_fmax_imp_awins:
	ret

.globl	whodun_unlock_imp
.type	whodun_unlock_imp, @function

whodun_unlock_imp:
	endbr64
	movq $1, %rax
	movq %rax, (%rdi)
	ret

.globl	whodun_tryLock_imp
.type	whodun_tryLock_imp, @function

whodun_tryLock_imp:
	endbr64
	xorq %rax, %rax
	xchg %rax, (%rdi)
	ret

.globl	whodun_atomGet_imp
.type	whodun_atomGet_imp, @function

whodun_atomGet_imp:
	endbr64
	movq (%rdi), %rax
	ret

.globl	whodun_atomicSet_imp
.type	whodun_atomicSet_imp, @function

whodun_atomicSet_imp:
	endbr64
	/* could do a simple move, but helgrind does not like it (for... understandable reasons), and contrary to guru wisdom there is value in shutting up valgrind */
	xchgq %rsi, (%rdi)
	ret

.globl	whodun_atomicSwap_imp
.type	whodun_atomicSwap_imp, @function

whodun_atomicSwap_imp:
	endbr64
	movq %rsi, %rax
	xchg %rax, (%rdi)
	ret

.globl	whodun_atomicCAS_imp
.type	whodun_atomicCAS_imp, @function

whodun_atomicCAS_imp:
	endbr64
	xorq %rcx, %rcx
	movq %rsi, %rax
	lock cmpxchgq %rdx, (%rdi)
	setz %cl
	movq %rcx, %rax
	ret

.globl	whodun_atomicAdd_imp
.type	whodun_atomicAdd_imp, @function

whodun_atomicAdd_imp:
	endbr64
	movq %rsi, %rax
	lock xadd %rax, (%rdi)
	addq %rsi, %rax
	ret


/*
whodun_UInt whodun_atomicAnd_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicOr_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicXor_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicMul_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);
whodun_Int whodun_atomicMin_imp(whodun_Int* toMang, whodun_Int withVal, whodun_Lock* toLock);
whodun_Int whodun_atomicMax_imp(whodun_Int* toMang, whodun_Int withVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicUMin_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);
whodun_UInt whodun_atomicUMax_imp(whodun_UInt* toMang, whodun_UInt withVal, whodun_Lock* toLock);
whodun_Float whodun_atomicFAdd_imp(void* toMang, whodun_Float withVal, whodun_Lock* toLock);
whodun_Float whodun_atomicFMul_imp(void* toMang, whodun_Float withVal, whodun_Lock* toLock);
whodun_Float whodun_atomicFMin_imp(void* toMang, whodun_Float withVal, whodun_Lock* toLock);
whodun_Float whodun_atomicFMax_imp(void* toMang, whodun_Float withVal, whodun_Lock* toLock);
*/




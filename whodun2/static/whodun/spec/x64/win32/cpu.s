
.text
.globl	whodun_packPtr_imp
.globl	whodun_unpackPtr_imp

whodun_packPtr_imp:
whodun_unpackPtr_imp:
	endbr64
	movq %rcx, %rax
	ret

.globl	whodun_packFlt_imp

whodun_packFlt_imp:
	endbr64
	subq $8, %rsp
	movsd %xmm0, (%rsp)
	movq (%rsp), %rax
	addq $8, %rsp
	ret

.globl	whodun_unpackFlt_imp

whodun_unpackFlt_imp:
	endbr64
	subq $8, %rsp
	movq %rcx, (%rsp)
	movsd (%rsp), %xmm0
	addq $8, %rsp
	ret

/*TODO check cmpq*/

.globl	whodun_min_imp

whodun_min_imp:
	endbr64
	movq %rcx, %rax
	cmpq %rdx, %rcx
	cmovg %rdx, %rax
	ret

.globl	whodun_max_imp

whodun_max_imp:
	endbr64
	movq %rdx, %rax
	cmpq %rdx, %rcx
	cmovg %rcx, %rax
	ret

.globl	whodun_umin_imp

whodun_umin_imp:
	endbr64
	movq %rcx, %rax
	cmpq %rdx, %rcx
	cmova %rdx, %rax
	ret

.globl	whodun_umax_imp

whodun_umax_imp:
	endbr64
	movq %rdx, %rax
	cmpq %rdx, %rcx
	cmova %rcx, %rax
	ret

.globl	whodun_fmin_imp

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

whodun_unlock_imp:
	endbr64
	movq $1, %rax
	movq %rax, (%rcx)
	ret

.globl	whodun_tryLock_imp

whodun_tryLock_imp:
	endbr64
	xorq %rax, %rax
	xchg %rax, (%rcx)
	ret

.globl	whodun_atomGet_imp

whodun_atomGet_imp:
	endbr64
	movq (%rcx), %rax
	ret

.globl	whodun_atomicSet_imp

whodun_atomicSet_imp:
	endbr64
	movq %rdx, (%rcx)
	ret

.globl	whodun_atomicSwap_imp

whodun_atomicSwap_imp:
	endbr64
	movq %rdx, %rax
	xchg %rax, (%rcx)
	ret

.globl	whodun_atomicCAS_imp

whodun_atomicCAS_imp:
	endbr64
	xorq %r9, %r9
	movq %rdx, %rax
	lock cmpxchgq %r8, (%rcx)
	setz %r9b
	movq %r9, %rax
	ret

.globl	whodun_atomicAdd_imp

whodun_atomicAdd_imp:
	endbr64
	movq %rdx, %rax
	lock xadd %rax, (%rcx)
	addq %rdx, %rax
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




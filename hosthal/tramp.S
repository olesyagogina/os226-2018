
.text
.global tramptramp
tramptramp:
	push %rax
	push %rcx
	push %rdx
	push %rsi
	push %r8
	push %r9
	push %r10
	push %r11
	/* FIXME vfp, xmm ...*/

	lea 80(%rsp), %rdi
	call *64(%rsp)

	pop %r11
	pop %r10
	pop %r9
	pop %r8
	pop %rsi
	pop %rdx
	pop %rcx
	pop %rax

	mov 8(%rsp), %rsp

	ret

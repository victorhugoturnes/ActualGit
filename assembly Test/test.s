	.file	"test.c"
	.intel_syntax noprefix
	.text
	.globl	_call
	.def	_call;	.scl	2;	.type	32;	.endef
_call:
	push	ebp
	mov	ebp, esp
	mov	eax, 1
	pop	ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	push	ebp
	mov	ebp, esp
	and	esp, -16
	call	___main
	call	_call
	mov	eax, 0
	leave
	ret
	.ident	"GCC: (tdm64-1) 5.1.0"

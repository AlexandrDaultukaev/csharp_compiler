	.text
	.file	"codegen_test1.cs"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               # -- Begin function main
.LCPI0_0:
	.quad	0x400999999999999a              # double 3.2000000000000002
.LCPI0_1:
	.quad	0x4008000000000000              # double 3
.LCPI0_2:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
	.cfi_offset %rbx, -24
	movsd	.LCPI0_1(%rip), %xmm0           # xmm0 = mem[0],zero
	movsd	%xmm0, -16(%rbp)
	movsd	-16(%rbp), %xmm0                # xmm0 = mem[0],zero
	movsd	.LCPI0_0(%rip), %xmm1           # xmm1 = mem[0],zero
	ucomisd	%xmm1, %xmm0
	jne	.LBB0_1
	jp	.LBB0_1
	jmp	.LBB0_6
.LBB0_1:                                # %v4
	movq	%rsp, %rbx
	addq	$-16, %rbx
	movq	%rbx, %rsp
	xorps	%xmm0, %xmm0
	movsd	%xmm0, (%rbx)
.LBB0_2:                                # %v7
                                        # =>This Inner Loop Header: Depth=1
	movsd	-16(%rbp), %xmm0                # xmm0 = mem[0],zero
	ucomisd	(%rbx), %xmm0
	jbe	.LBB0_5
# %bb.3:                                # %v12
                                        #   in Loop: Header=BB0_2 Depth=1
	movsd	-16(%rbp), %xmm0                # xmm0 = mem[0],zero
	movabsq	$.L.str.2, %rdi
	movb	$1, %al
	callq	printf@PLT
# %bb.4:                                # %v13
                                        #   in Loop: Header=BB0_2 Depth=1
	movsd	.LCPI0_2(%rip), %xmm0           # xmm0 = mem[0],zero
	addsd	(%rbx), %xmm0
	movsd	%xmm0, (%rbx)
	jmp	.LBB0_2
.LBB0_5:                                # %v8
	jmp	.LBB0_6
.LBB0_6:                                # %v5
	xorl	%eax, %eax
	leaq	-8(%rbp), %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d\n"
	.size	.L.str, 4

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%c\n"
	.size	.L.str.1, 4

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"%f\n"
	.size	.L.str.2, 4

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"%s\n"
	.size	.L.str.3, 4

	.section	".note.GNU-stack","",@progbits

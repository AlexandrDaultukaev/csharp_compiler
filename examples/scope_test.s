	.text
	.file	"scope_test.cs"
	.globl	func                            # -- Begin function func
	.p2align	4, 0x90
	.type	func,@function
func:                                   # @func
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movb	%sil, -1(%rbp)
	movsd	%xmm0, -40(%rbp)
	movl	%edi, -12(%rbp)
	movq	.L__const.func.funcprint, %rax
	movq	%rax, -23(%rbp)
	movw	.L__const.func.funcprint+8, %ax
	movw	%ax, -15(%rbp)
	movb	.L__const.func.funcprint+10, %al
	movb	%al, -13(%rbp)
	leaq	-23(%rbp), %rsi
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf@PLT
	movl	$151, -8(%rbp)
	movl	-8(%rbp), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf@PLT
	movl	-12(%rbp), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf@PLT
	movsd	-40(%rbp), %xmm0                # xmm0 = mem[0],zero
	movabsq	$.L.str.2, %rdi
	movb	$1, %al
	callq	printf@PLT
	movsbl	-1(%rbp), %esi
	movabsq	$.L.str.1, %rdi
	movb	$0, %al
	callq	printf@PLT
	movq	.L__const.func.funcprintend, %rax
	movq	%rax, -32(%rbp)
	movb	.L__const.func.funcprintend+8, %al
	movb	%al, -24(%rbp)
	leaq	-32(%rbp), %rsi
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf@PLT
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	func, .Lfunc_end0-func
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               # -- Begin function main
.LCPI1_0:
	.quad	0x4038333333333333              # double 24.199999999999999
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
	pushq	%r14
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	movl	$3, -20(%rbp)
	movl	$15, -28(%rbp)
	movb	$65, -21(%rbp)
	movsd	.LCPI1_0(%rip), %xmm0           # xmm0 = mem[0],zero
	movsd	%xmm0, -40(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
.LBB1_1:                                # %v39
                                        # =>This Inner Loop Header: Depth=1
	movl	-28(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jge	.LBB1_6
# %bb.2:                                # %v44
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	%rsp, %rax
	movq	%rax, %rsi
	addq	$-16, %rsi
	movq	%rsi, %rsp
	movabsq	$6998712986452847687, %rcx      # imm = 0x61206C61626F6C47
	movq	%rcx, -16(%rax)
	movb	$0, -8(%rax)
	movl	$.L.str.3, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	g0@GOTPCREL(%rip), %rax
	movl	(%rax), %esi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	%rsp, %rax
	movq	%rax, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	$1, -16(%rax)
	movq	%rsp, %rax
	movq	%rax, %r14
	addq	$-16, %r14
	movq	%r14, %rsp
	movl	$2, -16(%rax)
	movq	%rsp, %rax
	movq	%rax, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	$3, -16(%rax)
	movq	%rsp, %rbx
	addq	$-16, %rbx
	movq	%rbx, %rsp
	movl	$1, (%rbx)
	cmpl	$3, -20(%rbp)
	jne	.LBB1_4
# %bb.3:                                # %v59
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$5, (%r14)
	movq	%rsp, %rax
	addq	$-16, %rax
	movq	%rax, %rsp
	movl	$4, (%rax)
	movl	$4444, (%rbx)                   # imm = 0x115C
.LBB1_4:                                # %v60
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	%rsp, %rax
	movq	%rax, %rsi
	addq	$-16, %rsi
	movq	%rsi, %rsp
	movabsq	$29871997393792844, %rcx        # imm = 0x6A206C61636F4C
	movq	%rcx, -16(%rax)
	movl	$.L.str.3, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	(%rbx), %esi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	%rsp, %rax
	addq	$-16, %rax
	movq	%rax, %rsp
	movl	$2, (%rax)
	movl	$5, (%r14)
# %bb.5:                                # %v45
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	.LBB1_1
.LBB1_6:                                # %v40
	movq	%rsp, %rbx
	addq	$-16, %rbx
	movq	%rbx, %rsp
	movq	.L__const.main.message3, %rax
	movq	%rax, (%rbx)
	movb	.L__const.main.message3+8, %al
	movb	%al, 8(%rbx)
	movabsq	$.L.str.3, %rdi
	movq	%rbx, %rsi
	movb	$0, %al
	callq	printf@PLT
	movq	g1@GOTPCREL(%rip), %rax
	movl	(%rax), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf@PLT
.LBB1_7:                                # %v79
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$51, -20(%rbp)
	jge	.LBB1_10
# %bb.8:                                # %v83
                                        #   in Loop: Header=BB1_7 Depth=1
	movq	%rsp, %rax
	movq	%rax, %rcx
	addq	$-16, %rcx
	movq	%rcx, %rsp
	movl	$6, -16(%rax)
	movq	%rsp, %rax
	addq	$-16, %rax
	movq	%rax, %rsp
	movl	$7, (%rax)
	movq	g1@GOTPCREL(%rip), %rax
	movl	$8, (%rax)
# %bb.9:                                # %v84
                                        #   in Loop: Header=BB1_7 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	.LBB1_7
.LBB1_10:                               # %v80
	movabsq	$.L.str.3, %rdi
	movq	%rbx, %rsi
	movb	$0, %al
	callq	printf@PLT
	movq	g1@GOTPCREL(%rip), %rax
	movl	(%rax), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf@PLT
	cmpl	$2, -20(%rbp)
	jne	.LBB1_12
# %bb.11:                               # %v96
	movq	%rsp, %rax
	addq	$-16, %rax
	movq	%rax, %rsp
	movl	$242, (%rax)
	jmp	.LBB1_13
.LBB1_12:                               # %v97
	movq	%rsp, %rax
	addq	$-16, %rax
	movq	%rax, %rsp
	movl	$2, (%rax)
.LBB1_13:                               # %v98
	movl	-28(%rbp), %edi
	movsd	-40(%rbp), %xmm0                # xmm0 = mem[0],zero
	movzbl	-21(%rbp), %esi
	callq	func
	movq	%rsp, %rsi
	addq	$-16, %rsi
	movq	%rsi, %rsp
	movq	.L__const.main.message4, %rax
	movq	%rax, (%rsi)
	movb	.L__const.main.message4+8, %al
	movb	%al, 8(%rsi)
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf@PLT
	movq	g0@GOTPCREL(%rip), %rax
	movl	(%rax), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf@PLT
	xorps	%xmm0, %xmm0
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
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

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"%d"
	.size	.L.str.4, 3

	.type	.L.str.5,@object                # @.str.5
.L.str.5:
	.asciz	"%c"
	.size	.L.str.5, 3

	.type	.L.str.6,@object                # @.str.6
.L.str.6:
	.asciz	"%f"
	.size	.L.str.6, 3

	.type	.L.str.7,@object                # @.str.7
.L.str.7:
	.asciz	"%s"
	.size	.L.str.7, 3

	.type	g0,@object                      # @g0
	.data
	.globl	g0
	.p2align	2
g0:
	.long	243                             # 0xf3
	.size	g0, 4

	.type	g1,@object                      # @g1
	.globl	g1
	.p2align	2
g1:
	.long	5                               # 0x5
	.size	g1, 4

	.type	g2,@object                      # @g2
	.bss
	.globl	g2
	.p2align	2
g2:
	.long	0                               # 0x0
	.size	g2, 4

	.type	.L__const.func.funcprint,@object # @__const.func.funcprint
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__const.func.funcprint:
	.asciz	"func START"
	.size	.L__const.func.funcprint, 11

	.type	.L__const.func.funcprintend,@object # @__const.func.funcprintend
.L__const.func.funcprintend:
	.asciz	"func END"
	.size	.L__const.func.funcprintend, 9

	.type	.L__const.main.message,@object  # @__const.main.message
.L__const.main.message:
	.asciz	"Global a"
	.size	.L__const.main.message, 9

	.type	.L__const.main.message1,@object # @__const.main.message1
.L__const.main.message1:
	.asciz	"Local j"
	.size	.L__const.main.message1, 8

	.type	.L__const.main.message3,@object # @__const.main.message3
.L__const.main.message3:
	.asciz	"Global j"
	.size	.L__const.main.message3, 9

	.type	.L__const.main.message4,@object # @__const.main.message4
.L__const.main.message4:
	.asciz	"Global a"
	.size	.L__const.main.message4, 9

	.section	".note.GNU-stack","",@progbits

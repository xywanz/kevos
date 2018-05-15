	.file	"boot.32.cpp"
#APP
	.code32
	.align 4
#NO_APP
	.section	.boot,"a",@progbits
	.align 4
	.type	_ZL15multibootHeader, @object
	.size	_ZL15multibootHeader, 12
_ZL15multibootHeader:
	.long	464367618
	.long	3
	.long	-464367621
	.text
	.globl	entry32
	.type	entry32, @function
entry32:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$12, %esp
	pushl	$97
	call	isalpha
	addl	$16, %esp
.L2:
	jmp	.L2
	.cfi_endproc
.LFE2:
	.size	entry32, .-entry32
	.globl	_Z16setSegDescriptorP13SegDescriptorjjjhbb
	.type	_Z16setSegDescriptorP13SegDescriptorjjjhbb, @function
_Z16setSegDescriptorP13SegDescriptorjjjhbb:
.LFB3:
	.cfi_startproc
	subl	$12, %esp
	.cfi_def_cfa_offset 16
	movl	32(%esp), %ecx
	movl	36(%esp), %edx
	movl	40(%esp), %eax
	movb	%cl, 8(%esp)
	movb	%dl, 4(%esp)
	movb	%al, (%esp)
	movl	24(%esp), %eax
	movl	%eax, %edx
	movl	16(%esp), %eax
	movw	%dx, 2(%eax)
	movl	24(%esp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	movl	16(%esp), %eax
	movb	%dl, 4(%eax)
	movl	24(%esp), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	16(%esp), %eax
	movb	%dl, 7(%eax)
	movl	16(%esp), %eax
	movl	20(%esp), %edx
	movl	%edx, 8(%eax)
	movl	28(%esp), %eax
	movl	%eax, %edx
	movl	16(%esp), %eax
	movw	%dx, (%eax)
	movl	28(%esp), %eax
	shrl	$16, %eax
	andl	$15, %eax
	movl	16(%esp), %edx
	andl	$15, %eax
	movl	%eax, %ecx
	movzbl	6(%edx), %eax
	andl	$-16, %eax
	orl	%ecx, %eax
	movb	%al, 6(%edx)
	cmpb	$0, (%esp)
	je	.L4
	movl	$-119, %edx
	jmp	.L5
.L4:
	movl	$-110, %edx
.L5:
	movzbl	8(%esp), %eax
	sall	$5, %eax
	andl	$96, %eax
	orl	%eax, %edx
	cmpb	$0, 4(%esp)
	je	.L6
	movl	$8, %eax
	jmp	.L7
.L6:
	movl	$0, %eax
.L7:
	orl	%edx, %eax
	movl	%eax, %edx
	movl	16(%esp), %eax
	movb	%dl, 5(%eax)
	cmpb	$0, 4(%esp)
	je	.L8
	movl	$10, %edx
	jmp	.L9
.L8:
	movl	$12, %edx
.L9:
	movl	16(%esp), %eax
	movl	%edx, %ecx
	sall	$4, %ecx
	movzbl	6(%eax), %edx
	andl	$15, %edx
	orl	%ecx, %edx
	movb	%dl, 6(%eax)
	nop
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE3:
	.size	_Z16setSegDescriptorP13SegDescriptorjjjhbb, .-_Z16setSegDescriptorP13SegDescriptorjjjhbb
#APP
	.code64
	.ident	"GCC: (Ubuntu 7.2.0-1ubuntu1~14.04) 7.2.0"
	.section	.note.GNU-stack,"",@progbits

	.file	"boot.32.cpp"
#APP
	.code32
	.align 4
#NO_APP
	.section	.boot,"a",@progbits
	.align 4
	.type	_ZN4arch3x866commonL15multibootHeaderE, @object
	.size	_ZN4arch3x866commonL15multibootHeaderE, 12
_ZN4arch3x866commonL15multibootHeaderE:
	.long	464367618
	.long	3
	.long	-464367621
	.globl	_ZN4arch3x863x644boot17__knStackOfBoot32E
	.bss
	.align 4096
	.type	_ZN4arch3x863x644boot17__knStackOfBoot32E, @object
	.size	_ZN4arch3x863x644boot17__knStackOfBoot32E, 8192
_ZN4arch3x863x644boot17__knStackOfBoot32E:
	.zero	8192
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
	subl	$24, %esp
#APP
# 72 "boot.32.cpp" 1
	movl $_ZN4arch3x863x644boot17__knStackOfBoot32E+8192,%esp
# 0 "" 2
#NO_APP
	call	_ZN4arch3x863x644bootL16clearFrameBufferEv
	call	_ZN4arch3x863x644bootL8clearBSSEv
	call	_ZN4arch3x863x644bootL15setupKernelPageEv
	call	_ZN4arch3x863x644bootL6setPAEEv
	call	_ZN4arch3x863x644bootL8setupCR3Ev
	call	_ZN4arch3x863x644bootL14enableLongModeEv
	call	_ZN4arch3x863x644bootL12enablePagingEv
	subl	$8, %esp
	pushl	$1
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$1
	call	_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh
	addl	$32, %esp
	subl	$8, %esp
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$2
	call	_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh
	addl	$32, %esp
	subl	$8, %esp
	pushl	$1
	pushl	$3
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$3
	call	_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh
	addl	$32, %esp
	subl	$8, %esp
	pushl	$0
	pushl	$3
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$4
	call	_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh
	addl	$32, %esp
	movw	$79, -14(%ebp)
	movl	$_ZN4arch3x863x647__knGDTE, %eax
	movl	%eax, -12(%ebp)
#APP
# 93 "boot.32.cpp" 1
	lgdt -14(%ebp)
# 0 "" 2
#NO_APP
	movl	$32, %eax
#APP
# 101 "boot.32.cpp" 1
	mov %ax,%ds
mov %ax,%es
mov %ax,%ss
mov %ax,%fs
mov %ax,%gs

# 0 "" 2
# 102 "boot.32.cpp" 1
	ljmp $16,$entry64

# 0 "" 2
#NO_APP
	.cfi_endproc
.LFE2:
	.size	entry32, .-entry32
	.type	_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh, @function
_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh:
.LFB3:
	.cfi_startproc
	subl	$24, %esp
	.cfi_def_cfa_offset 28
	movl	44(%esp), %edx
	movl	48(%esp), %eax
	movb	%dl, 4(%esp)
	movb	%al, (%esp)
	movl	28(%esp), %eax
	sall	$4, %eax
	addl	$_ZN4arch3x863x647__knGDTE, %eax
	movl	%eax, 20(%esp)
	movl	40(%esp), %eax
	movl	%eax, %edx
	movl	20(%esp), %eax
	movw	%dx, (%eax)
	movl	20(%esp), %eax
	addl	$2, %eax
	movl	36(%esp), %edx
	movw	%dx, (%eax)
	movl	36(%esp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	movl	20(%esp), %eax
	addl	$4, %eax
	movb	%dl, (%eax)
	movzbl	4(%esp), %eax
	sall	$5, %eax
	andl	$96, %eax
	orl	$-110, %eax
	movl	%eax, %edx
	cmpb	$0, (%esp)
	je	.L3
	movl	$8, %eax
	jmp	.L4
.L3:
	movl	$0, %eax
.L4:
	orl	%eax, %edx
	movl	20(%esp), %eax
	addl	$5, %eax
	movb	%dl, (%eax)
	movl	40(%esp), %eax
	shrl	$16, %eax
	andl	$15, %eax
	movl	%eax, %edx
	cmpb	$0, (%esp)
	je	.L5
	movl	$-96, %ecx
	jmp	.L6
.L5:
	movl	$-64, %ecx
.L6:
	movl	20(%esp), %eax
	addl	$6, %eax
	orl	%ecx, %edx
	movb	%dl, (%eax)
	movl	36(%esp), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	20(%esp), %eax
	addl	$7, %eax
	movb	%dl, (%eax)
	movl	20(%esp), %eax
	leal	8(%eax), %edx
	movl	32(%esp), %eax
	movl	%eax, (%edx)
	movl	20(%esp), %eax
	addl	$12, %eax
	movl	$0, (%eax)
	nop
	addl	$24, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE3:
	.size	_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh, .-_ZN4arch3x863x644bootL19setSystemDescriptorEjjjjhh
	.type	_ZN4arch3x863x644bootL5bzeroEPcj, @function
_ZN4arch3x863x644bootL5bzeroEPcj:
.LFB4:
	.cfi_startproc
	subl	$16, %esp
	.cfi_def_cfa_offset 20
	movl	24(%esp), %eax
	shrl	$2, %eax
	movl	%eax, 12(%esp)
	movl	24(%esp), %eax
	andl	$3, %eax
	movl	%eax, 8(%esp)
	movl	20(%esp), %eax
	movl	%eax, 4(%esp)
.L9:
	movl	12(%esp), %eax
	leal	-1(%eax), %edx
	movl	%edx, 12(%esp)
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L8
	movl	4(%esp), %eax
	leal	4(%eax), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%eax)
	jmp	.L9
.L8:
	movl	4(%esp), %eax
	movl	%eax, 20(%esp)
.L11:
	movl	8(%esp), %eax
	leal	-1(%eax), %edx
	movl	%edx, 8(%esp)
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L12
	movl	4(%esp), %eax
	leal	4(%eax), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%eax)
	jmp	.L11
.L12:
	nop
	addl	$16, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE4:
	.size	_ZN4arch3x863x644bootL5bzeroEPcj, .-_ZN4arch3x863x644bootL5bzeroEPcj
	.type	_ZN4arch3x863x644bootL16clearFrameBufferEv, @function
_ZN4arch3x863x644bootL16clearFrameBufferEv:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	$2000
	pushl	$753664
	call	_ZN4arch3x863x644bootL5bzeroEPcj
	addl	$8, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	_ZN4arch3x863x644bootL16clearFrameBufferEv, .-_ZN4arch3x863x644bootL16clearFrameBufferEv
	.type	_ZN4arch3x863x644bootL8clearBSSEv, @function
_ZN4arch3x863x644bootL8clearBSSEv:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$bss_end_address, %edx
	movl	$bss_start_address, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sarl	$3, %eax
	pushl	%eax
	pushl	$bss_start_address
	call	_ZN4arch3x863x644bootL5bzeroEPcj
	addl	$8, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	_ZN4arch3x863x644bootL8clearBSSEv, .-_ZN4arch3x863x644bootL8clearBSSEv
	.type	_ZN4arch3x863x644bootL6setPAEEv, @function
_ZN4arch3x863x644bootL6setPAEEv:
.LFB7:
	.cfi_startproc
#APP
# 154 "boot.32.cpp" 1
	mov %cr4,%eax
or $0x20, %eax
mov %eax,%cr4

# 0 "" 2
#NO_APP
	nop
	ret
	.cfi_endproc
.LFE7:
	.size	_ZN4arch3x863x644bootL6setPAEEv, .-_ZN4arch3x863x644bootL6setPAEEv
	.type	_ZN4arch3x863x644bootL15setupKernelPageEv, @function
_ZN4arch3x863x644bootL15setupKernelPageEv:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$48, %esp
	pushl	$4096
	pushl	$_ZN4arch3x863x648__knPML4E
	call	_ZN4arch3x863x644bootL5bzeroEPcj
	addl	$8, %esp
	pushl	$4096
	pushl	$_ZN4arch3x863x648__knPDPTE
	call	_ZN4arch3x863x644bootL5bzeroEPcj
	addl	$8, %esp
	pushl	$2097152
	pushl	$_ZN4arch3x863x647__knPDTE
	call	_ZN4arch3x863x644bootL5bzeroEPcj
	addl	$8, %esp
	pushl	$67108864
	pushl	$_ZN4arch3x863x646__knPTE
	call	_ZN4arch3x863x644bootL5bzeroEPcj
	addl	$8, %esp
	movl	$_ZN4arch3x863x648__knPML4E, -36(%ebp)
	movl	$_ZN4arch3x863x648__knPDPTE, -40(%ebp)
	movl	$_ZN4arch3x863x647__knPDTE, -44(%ebp)
	movl	$_ZN4arch3x863x646__knPTE, -48(%ebp)
	movl	$0, -4(%ebp)
	movl	-40(%ebp), %eax
	addl	$3, %eax
	movl	%eax, -8(%ebp)
.L18:
	cmpl	$0, -4(%ebp)
	jne	.L17
	movl	-36(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-36(%ebp), %eax
	addl	$8, %eax
	movl	%eax, -36(%ebp)
	addl	$1, -4(%ebp)
	addl	$4096, -8(%ebp)
	jmp	.L18
.L17:
	movl	$0, -12(%ebp)
	movl	-44(%ebp), %eax
	addl	$3, %eax
	movl	%eax, -16(%ebp)
.L20:
	cmpl	$0, -12(%ebp)
	jne	.L19
	movl	-40(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, (%eax)
	movl	-40(%ebp), %eax
	addl	$8, %eax
	movl	%eax, -40(%ebp)
	addl	$1, -12(%ebp)
	addl	$4096, -16(%ebp)
	jmp	.L20
.L19:
	movl	$0, -20(%ebp)
	movl	-48(%ebp), %eax
	addl	$3, %eax
	movl	%eax, -24(%ebp)
.L22:
	cmpl	$31, -20(%ebp)
	ja	.L21
	movl	-44(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%edx, (%eax)
	movl	-44(%ebp), %eax
	addl	$8, %eax
	movl	%eax, -44(%ebp)
	addl	$1, -20(%ebp)
	addl	$4096, -24(%ebp)
	jmp	.L22
.L21:
	movl	$0, -28(%ebp)
	movl	$3, -32(%ebp)
.L24:
	cmpl	$16383, -28(%ebp)
	ja	.L25
	movl	-48(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, (%eax)
	movl	-48(%ebp), %eax
	addl	$8, %eax
	movl	%eax, -48(%ebp)
	addl	$1, -28(%ebp)
	addl	$4096, -32(%ebp)
	jmp	.L24
.L25:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	_ZN4arch3x863x644bootL15setupKernelPageEv, .-_ZN4arch3x863x644bootL15setupKernelPageEv
	.type	_ZN4arch3x863x644bootL14enableLongModeEv, @function
_ZN4arch3x863x644bootL14enableLongModeEv:
.LFB9:
	.cfi_startproc
#APP
# 204 "boot.32.cpp" 1
	mov $0xC0000080,%ecx
rdmsr
or $0x900,%eax
wrmsr

# 0 "" 2
#NO_APP
	nop
	ret
	.cfi_endproc
.LFE9:
	.size	_ZN4arch3x863x644bootL14enableLongModeEv, .-_ZN4arch3x863x644bootL14enableLongModeEv
	.type	_ZN4arch3x863x644bootL8setupCR3Ev, @function
_ZN4arch3x863x644bootL8setupCR3Ev:
.LFB10:
	.cfi_startproc
	movl	$_ZN4arch3x863x648__knPML4E, %eax
#APP
# 209 "boot.32.cpp" 1
	mov %eax,%cr3
# 0 "" 2
#NO_APP
	nop
	ret
	.cfi_endproc
.LFE10:
	.size	_ZN4arch3x863x644bootL8setupCR3Ev, .-_ZN4arch3x863x644bootL8setupCR3Ev
	.type	_ZN4arch3x863x644bootL12enablePagingEv, @function
_ZN4arch3x863x644bootL12enablePagingEv:
.LFB11:
	.cfi_startproc
#APP
# 218 "boot.32.cpp" 1
	mov %cr0,%eax
or $0x80000001,%eax
mov %eax,%cr0

# 0 "" 2
#NO_APP
	nop
	ret
	.cfi_endproc
.LFE11:
	.size	_ZN4arch3x863x644bootL12enablePagingEv, .-_ZN4arch3x863x644bootL12enablePagingEv
#APP
	.code64
	.align 8
	.ident	"GCC: (Ubuntu 7.2.0-1ubuntu1~14.04) 7.2.0"
	.section	.note.GNU-stack,"",@progbits

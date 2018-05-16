	.file	"boot.32.cpp"
#APP
	.code32
	.align 4
	.equ VIRTUAL_START_ADDRESS,0xFFFFFFFF80000000
#NO_APP
	.section	.boot,"a",@progbits
	.align 4
	.type	_ZL15multibootHeader, @object
	.size	_ZL15multibootHeader, 12
_ZL15multibootHeader:
	.long	464367618
	.long	3
	.long	-464367621
	.globl	__knGDT
	.bss
	.align 32
	.type	__knGDT, @object
	.size	__knGDT, 80
__knGDT:
	.zero	80
	.text
	.globl	entry32
	.type	entry32, @function
entry32:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$8, %esp
	pushl	$2000
	pushl	$753664
	call	_ZL5bzeroPcj
	addl	$16, %esp
	movl	$bss_end_address+2147483647, %eax
	movl	%eax, %edx
	movl	$bss_start_address+2147483647, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	$bss_start_address+2147483647, %edx
	addl	$1, %edx
	subl	$8, %esp
	pushl	%eax
	pushl	%edx
	call	_ZL5bzeroPcj
	addl	$16, %esp
	call	_ZL22initializeBootTimePagev
#APP
# 76 "../../kevos/src/arch/x64/boot.32.cpp" 1
	mov %cr4,%eax
or $0x20, %eax
mov %eax,%cr4

# 0 "" 2
#NO_APP
	movl	$__knPML4+2147483647, %eax
	addl	$1, %eax
#APP
# 77 "../../kevos/src/arch/x64/boot.32.cpp" 1
	mov %eax,%cr3
# 0 "" 2
# 81 "../../kevos/src/arch/x64/boot.32.cpp" 1
	mov $0xC0000080,%ecx
rdmsr
or $0x900,%eax
wrmsr

# 0 "" 2
# 83 "../../kevos/src/arch/x64/boot.32.cpp" 1
	push $2
popf

# 0 "" 2
# 86 "../../kevos/src/arch/x64/boot.32.cpp" 1
	mov %cr0,%eax
or $0x80000001,%eax
mov %eax,%cr0

# 0 "" 2
#NO_APP
	movw	$79, -14(%ebp)
	movl	$__knGDT+2147483647, %eax
	addl	$1, %eax
	movl	%eax, -12(%ebp)
#APP
# 95 "../../kevos/src/arch/x64/boot.32.cpp" 1
	lgdt -14(%ebp)
# 0 "" 2
# 102 "../../kevos/src/arch/x64/boot.32.cpp" 1
	ljmp $24,$entry64-VIRTUAL_START_ADDRESS

# 0 "" 2
#NO_APP
.L2:
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	entry32, .-entry32
	.type	_ZL5bzeroPcj, @function
_ZL5bzeroPcj:
.LFB1:
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
.L5:
	movl	12(%esp), %eax
	leal	-1(%eax), %edx
	movl	%edx, 12(%esp)
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L4
	movl	4(%esp), %eax
	leal	4(%eax), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%eax)
	jmp	.L5
.L4:
	movl	4(%esp), %eax
	movl	%eax, 20(%esp)
.L7:
	movl	8(%esp), %eax
	leal	-1(%eax), %edx
	movl	%edx, 8(%esp)
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L8
	movl	4(%esp), %eax
	leal	4(%eax), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%eax)
	jmp	.L7
.L8:
	nop
	addl	$16, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1:
	.size	_ZL5bzeroPcj, .-_ZL5bzeroPcj
	.type	_ZL20setSegmentDescriptorP17SegmentDescriptorjjjhhh, @function
_ZL20setSegmentDescriptorP17SegmentDescriptorjjjhhh:
.LFB2:
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
	je	.L10
	movl	$-119, %edx
	jmp	.L11
.L10:
	movl	$-110, %edx
.L11:
	movzbl	8(%esp), %eax
	sall	$5, %eax
	andl	$96, %eax
	orl	%eax, %edx
	cmpb	$0, 4(%esp)
	je	.L12
	movl	$8, %eax
	jmp	.L13
.L12:
	movl	$0, %eax
.L13:
	orl	%edx, %eax
	movl	%eax, %edx
	movl	16(%esp), %eax
	movb	%dl, 5(%eax)
	cmpb	$0, 4(%esp)
	je	.L14
	movl	$10, %edx
	jmp	.L15
.L14:
	movl	$12, %edx
.L15:
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
.LFE2:
	.size	_ZL20setSegmentDescriptorP17SegmentDescriptorjjjhhh, .-_ZL20setSegmentDescriptorP17SegmentDescriptorjjjhhh
	.type	_ZL22initializeBootTimePagev, @function
_ZL22initializeBootTimePagev:
.LFB3:
	.cfi_startproc
#APP
# 135 "../../kevos/src/arch/x64/boot.32.cpp" 1
	movl $__knPDPT-VIRTUAL_START_ADDRESS+3,__knPML4-VIRTUAL_START_ADDRESS
movl $0,__knPML4-VIRTUAL_START_ADDRESS+4

# 0 "" 2
# 137 "../../kevos/src/arch/x64/boot.32.cpp" 1
	movl $__knPDT-VIRTUAL_START_ADDRESS+3,__knPDPT-VIRTUAL_START_ADDRESS
movl $0,__knPDPT-VIRTUAL_START_ADDRESS+4

# 0 "" 2
# 139 "../../kevos/src/arch/x64/boot.32.cpp" 1
	movl $0x83, __knPDT-VIRTUAL_START_ADDRESS
movl $0, __knPDT-VIRTUAL_START_ADDRESS+4

# 0 "" 2
#NO_APP
	nop
	ret
	.cfi_endproc
.LFE3:
	.size	_ZL22initializeBootTimePagev, .-_ZL22initializeBootTimePagev
#APP
	.code64
	.ident	"GCC: (Ubuntu 7.2.0-1ubuntu1~14.04) 7.2.0"
	.section	.note.GNU-stack,"",@progbits

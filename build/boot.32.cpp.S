	.file	"boot.32.cpp"
#APP
	.code32
	.align 4
#NO_APP
	.text
	.type	_ZL16setSegDescriptorP13SegDescriptor, @function
_ZL16setSegDescriptorP13SegDescriptor:
.LFB0:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE0:
	.size	_ZL16setSegDescriptorP13SegDescriptor, .-_ZL16setSegDescriptorP13SegDescriptor
	.globl	entry32
	.type	entry32, @function
entry32:
.LFB1:
	.cfi_startproc
#APP
# 47 "../../kevos/src/arch/x64/boot.32.cpp" 1
	movl $0xB8000,%eax
# 0 "" 2
# 48 "../../kevos/src/arch/x64/boot.32.cpp" 1
	movb $75,0(%eax)
# 0 "" 2
# 49 "../../kevos/src/arch/x64/boot.32.cpp" 1
	movb $75,1(%eax)
# 0 "" 2
#NO_APP
.L3:
	jmp	.L3
	.cfi_endproc
.LFE1:
	.size	entry32, .-entry32
	.section	.boot,"a",@progbits
	.align 4
	.type	_ZL15multibootHeader, @object
	.size	_ZL15multibootHeader, 12
_ZL15multibootHeader:
	.long	464367618
	.long	3
	.long	-464367621
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5"
	.section	.note.GNU-stack,"",@progbits

/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

.code64
.text

.equ KERNEL_DS,0x20

.macro setupSegment
	movw $KERNEL_DS,%ax
	movw %ax,%ds
	movw %ax,%ss
	movw %ax,%es
	movw %ax,%fs
	movw %ax,%gs
.endm

.macro save
	pushq %rsp
	pushq %rax
	pushq %rcx
	pushq %rdx
	pushq %rbx
	pushq %rbp
	pushq %rsi
	pushq %rdi
	pushq %r8
	pushq %r9
	pushq %r10
	pushq %r11
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
.endm

.macro load
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %r11
	popq %r10
	popq %r9
	popq %r8
	popq %rdi
	popq %rsi
	popq %rbp
	popq %rbx
	popq %rdx
	popq %rcx
	popq %rax
	popq %rsp
.endm


.macro irqAsmHandler number
.global irqAsmHandler\number
.extern irqCppHandler\number
irqAsmHandler\number:
	save
	call irqCppHandler\number
	load
	iretq
.endm

.irp number,0,1
irqAsmHandler \number
.endr

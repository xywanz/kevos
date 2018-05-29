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

.equ __KERNEL_DS,0x20

.macro setupSegment
    movw $__KERNEL_DS,%ax
    movw %ax,%ds
    movw %ax,%ss
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
.endm

.macro save
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    movw %ds,%ax
    pushq %ax
    movw %es,%ax
    pushq %ax
    movw $__KERNEL_DS,%ax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%ss
    movw %ax,%fs
    movw %ax,%gs
.endm

.macro load
    popq %rax
    movw %ax,%es
    popq %rax
    movw %ax,%ds
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax
.endm


.extern irqHandlers
.extern saveProcessRegisters
.extern switchToContext

.macro irqAsmHandler number
.global irqAsmHandler\number
irqAsmHandler\number:
    save
    movq %rsp,%rdi
    callq saveProcessRegisters
    movq $\number,%rdi
    mov $irqHandlers,%rax
    mov $\number,%rbx
    callq *(%rax,%rbx,8)
    callq switchToContext
    load
    iretq
.endm

.irp number,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
irqAsmHandler \number
.endr

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
    movw %ax,%es
    movw %ax,%ss
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
    setupSegment
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


.extern interruptHandlers
.extern saveProcessRegisters

.equ FAULT0,0
.macro faultAsmHandler number
.global faultAsmHandler\number
faultAsmHandler\number:
    save
    movq %rsp,%rdi
    callq saveProcessRegisters
    movq $\number,%rdi
    mov $interruptHandlers,%rax
    mov $\number+FAULT0,%rbx
    callq *(%rax,%rbx,8)
    load
    iretq
.endm

.irp number,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
faultAsmHandler \number
.endr


.equ IRQ0,0x20
.macro irqAsmHandler number
.global irqAsmHandler\number
irqAsmHandler\number:
    save
    movq %rsp,%rdi
    callq saveProcessRegisters
    mov $interruptHandlers,%rax
    mov $\number+IRQ0,%rbx
    callq *(%rax,%rbx,8)
    load
    iretq
.endm

.irp number,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
irqAsmHandler \number
.endr


.equ SYSCALL0,0x80
.macro syscallAsmHandler number
.global syscallAsmHandler\number
syscallAsmHandler\number:
    save
    movq %rsp,%rdi
    callq saveProcessRegisters
    mov $interruptHandlers,%rax
    mov $\number+SYSCALL0,%rbx
    callq *(%rax,%rbx,8)
    load
    iretq
.endm

.irp number,0,1,2,3,4,5,6,7
syscallAsmHandler \number
.endr

.global forceScheduleAsmHandler
forceScheduleAsmHandler:
    save
    movq %rsp,%rdi
    callq saveProcessRegisters
    mov $interruptHandlers,%rax
    mov $0x79,%rbx
    callq *(%rax,%rbx,8)
    load
    iretq


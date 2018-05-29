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

#ifndef _KEVOS_ARCH_x86_X64_INTERRUPT_H_
#define _KEVOS_ARCH_x86_X64_INTERRUPT_H_

#include <arch/common/types.h>

KEVOS_NSS_3(arch,x86,x64);

#define IRQ_TIMER		0
#define IRQ_KEYBOARD	1

struct SoftwareSavedRegisters
{
    uint64_t es;
    uint64_t ds;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t rsp;
};

/**
 * @brief 中断服务的返回信息
 *
 *    中断会引起CPU的特权级变为0，能够使得CPU从用户态变为内核态，这时CPU需要保存返回用户态的信息，即堆栈的切换操
 * 作。CPU首先从TSS取得内核栈选择子ss0及偏移rsp0，将堆栈切换到内核态，然后CPU将按ss、rsp、rflags、cs、rip的顺序
 * 将用户态的上述寄存器压入内核栈内。
 */
struct HardwareSavedRegisters
{
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
};

extern "C"
{

void irqAsmHandler0();
void irqAsmHandler1();
void irqAsmHandler2();
void irqAsmHandler3();
void irqAsmHandler4();
void irqAsmHandler5();
void irqAsmHandler6();
void irqAsmHandler7();
void irqAsmHandler8();
void irqAsmHandler9();
void irqAsmHandler10();
void irqAsmHandler11();
void irqAsmHandler12();
void irqAsmHandler13();
void irqAsmHandler14();
void irqAsmHandler15();

void irqCppHandler(uint64_t irq);

void irqCppHandler0();
void irqCppHandler1();
void irqCppHandler2();
void irqCppHandler3();
void irqCppHandler4();
void irqCppHandler5();
void irqCppHandler6();
void irqCppHandler7();
void irqCppHandler8();
void irqCppHandler9();
void irqCppHandler10();
void irqCppHandler11();
void irqCppHandler12();
void irqCppHandler13();
void irqCppHandler14();
void irqCppHandler15();

}

KEVOS_NSE_3(x64,x86,arch);

#endif

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
};

extern "C"
{

void saveProcessRegisters(char* base);
void switchToContext();


/**
 * @brief 除法错误，被0除
 */
void faultAsmHandler0();

/**
 * @brief 调试异常
 */
void faultAsmHandler1();

/**
 * @brief NMI中断，不可屏蔽中断，如电源掉电等
 */
void faultAsmHandler2();

/**
 * @brief 断点，执行int 3指令时，可用于调试
 */
void faultAsmHandler3();

/**
 * @brief 溢出
 */
void faultAsmHandler4();

/**
 * @brief 边界检测
 */
void faultAsmHandler5();

/**
 * @brief 无效操作码
 */
void faultAsmHandler6();

/**
 * @brief 设备不可用
 */
void faultAsmHandler7();

/**
 * @brief 双重故障
 */
void faultAsmHandler8();

/**
 * @brief 协处理器段越界
 */
void faultAsmHandler9();

/**
 * @brief 无效TSS
 */
void faultAsmHandler10();

/**
 * @brief 缺段异常
 */
void faultAsmHandler11();

/**
 * @brief 堆栈异常
 */
void faultAsmHandler12();

/**
 * @brief 一般保护异常
 */
void faultAsmHandler13();

/**
 * @brief 页异常（缺页中断）
 */
void faultAsmHandler14();

/**
 * @brief 保留
 */
void faultAsmHandler15();

/**
 * @brief 协处理器出错
 */
void faultAsmHandler16();

/**
 * @brief 对齐检查中断，操作数地址没有被正确地排列
 */
void faultAsmHandler17();

/**
 * @brief 机器检查，检测到CPU或总线错误
 */
void faultAsmHandler18();

/**
 * @brief SIMD协处理器出错，遇到不能处理的指令
 */
void faultAsmHandler19();

/**
 * @brief 20-31保留
 */
void faultAsmHandler20();
void faultAsmHandler21();
void faultAsmHandler22();
void faultAsmHandler23();
void faultAsmHandler24();
void faultAsmHandler25();
void faultAsmHandler26();
void faultAsmHandler27();
void faultAsmHandler28();
void faultAsmHandler29();
void faultAsmHandler30();
void faultAsmHandler31();

void faultCppHandler0();
void faultCppHandler1();
void faultCppHandler2();
void faultCppHandler3();
void faultCppHandler4();
void faultCppHandler5();
void faultCppHandler6();
void faultCppHandler7();
void faultCppHandler8();
void faultCppHandler9();
void faultCppHandler10();
void faultCppHandler11();
void faultCppHandler12();
void faultCppHandler13();
void faultCppHandler14();
void faultCppHandler15();
void faultCppHandler16();
void faultCppHandler17();
void faultCppHandler18();
void faultCppHandler19();
void faultCppHandler20();
void faultCppHandler21();
void faultCppHandler22();
void faultCppHandler23();
void faultCppHandler24();
void faultCppHandler25();
void faultCppHandler26();
void faultCppHandler27();
void faultCppHandler28();
void faultCppHandler29();
void faultCppHandler30();
void faultCppHandler31();



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



void syscallAsmHandler0();
void syscallAsmHandler1();
void syscallAsmHandler2();
void syscallAsmHandler3();
void syscallAsmHandler4();
void syscallAsmHandler5();
void syscallAsmHandler6();
void syscallAsmHandler7();

void syscallCppHandler0();
void syscallCppHandler1();
void syscallCppHandler2();
void syscallCppHandler3();
void syscallCppHandler4();
void syscallCppHandler5();
void syscallCppHandler6();
void syscallCppHandler7();

}

KEVOS_NSE_3(x64,x86,arch);

#endif

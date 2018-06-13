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

/*32位保护模式的启动代码，设置好环境后跳转到64位长模式

  保护模式到长模式6步：
    1. 设置并加载GDT
    2. 初始化页表（不能打开分页，打开分页后自动进入了长模式）
    3. 设置CR4.PAE=1
    4. 设置EFER.LME=1
    5. 设置CR0.PG=1进入分页模式
    6. 处理器自动设置EFER.LMA，并进入长模式，然后跳转到64位代码

  此段代码编译成32位代码，4字节对齐
*/

__asm__(".code32");
__asm__(".align 4");

#include <arch/common/config.h>
#include <arch/x86/x64/page_defs.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/kpaging.h>
#include <kernel/mm/mem_layout.h>

#include <cstddef>

#ifdef __KEVOS_MULTIBOOT__
#include <arch/x86/common/multiboot.h>
#endif

/**
 * 此处是为了确保整形的size
 */
static_assert(sizeof(uint8_t)==1,"In x86-64 achitecture, uint8_t must be 1 byte!");
static_assert(sizeof(int8_t)==1,"In x86-64 achitecture, int8_t must be 1 bytes!");
static_assert(sizeof(uint16_t)==2,"In x86-64 achitecture, uint16_t must be 2 bytes!");
static_assert(sizeof(int16_t)==2,"In x86-64 achitecture, int16_t must be 2 bytes!");
static_assert(sizeof(uint32_t)==4,"In x86-64 achitecture, uint32_t must be 4 bytes!");
static_assert(sizeof(int32_t)==4,"In x86-64 achitecture, int32_t must be 4 bytes!");
static_assert(sizeof(uint64_t)==8,"In x86-64 achitecture, uint64_t must be 8 bytes!");
static_assert(sizeof(int64_t)==8,"In x86-64 achitecture, int64_t must be 8 bytes!");
static_assert(sizeof(std::size_t)==8,"In x86-64 achitecture, std::size_t must be 8 bytes!");

namespace boot
{

using namespace mm::page;

/**
 * 设置内核段描述符
 * 段描述符网上的资料应该比较多，如有不明白可邮箱联系
 */
static void setSystemDescriptor(uint32_t index,uint32_t baseHigh,uint32_t baseLow,
            uint32_t limit,uint8_t dpl,uint8_t code);

/**
 * 内存清零
 */
static void bzero(char* p,uint32_t size);

/**
 * 由于kevos还没有提供一个良好的显示界面，暂时使用grub2默认跳转进入的80x25的字符模式
 * 在字符模式中，内存0xB8000处开始的80x25x2个字节的内容将与屏幕上的每个位置一一对应。
 * 即在对应位置内存写入内容，屏幕上会自动显示。
 * 每个字符占2个字节，高字节代表颜色，低字节代表要显示的ASCII。
 * 该函数将显示缓冲区清空。
 */
static void clearFrameBuffer();

/**
 * 将内核bss段清零，实际上不清零也可
 */ 
static void clearBSS();

/**
 * 开启地址线扩展，启用之后才能进行64位寻址，PAE是CR4第5位
 */
static void setPAE();

/**
 * 设置内核分页
 * 内核占用0-0xFFFFFFFF 4GB的空间，用户空间从0x100000000开始到0x0000FFFFFFFFFFFF
 * 暂时只针对48位寻址的CPU进行开发
 */
static void setupKernelPage();

/**
 * 设置ERER.LME=1，进入长模式
 */
static void enableLongMode();

/**
 * 加载pml4到cr3
 */
static void setupCR3();

/**
 * 64位模式废弃了段寻址，且必须开启分页
 * 开启分页后进入了长模式，然后设置长模式下的GDT,通过一个ljmp跳转入64位代码
 */
static void enablePaging();

extern "C" void entry32()
{
    clearFrameBuffer();     // Done!    
    clearBSS();             // Done!
    setupKernelPage();      // Done!
    setPAE();               // Done!
    setupCR3();             // Done!
    enableLongMode();       // Done!
    enablePaging();         // Done!

    // 设置GDT及段寄存器，最后将跳到64位长模式
    setSystemDescriptor(1, 0, 0, 0, 0, 1);
    setSystemDescriptor(2, 0, 0, 0, 0, 0);
    struct __packed__ GDTPointer
    {
        uint16_t limit;
        uint32_t address;
    } gdtPtr={
        sizeof(desc::gdt::items)-1,
        reinterpret_cast<uint32_t>(desc::gdt::items)
    };
    __asm__ __volatile__("lgdt %[gdtr]" : : [gdtr]"m"(gdtPtr));
    __asm__ __volatile__(
        "mov %%ax,%%ds\n"
        "mov %%ax,%%es\n"
        "mov %%ax,%%ss\n"
        "mov %%ax,%%fs\n"
        "mov %%ax,%%gs\n"
        : : "a"(__KERNEL_DS)
    );
    __asm__ __volatile__("movl %[stack],%%esp": : [stack]"i"(reinterpret_cast<uint32_t>(&kstack_end_address)));
    __asm__ __volatile__("ljmp %[cs],$entry64\n": : [cs]"i"(__KERNEL_CS));

    __unreachable__();
}


static void setSystemDescriptor(uint32_t index,uint32_t baseHigh,uint32_t baseLow,
            uint32_t limit,uint8_t dpl,uint8_t code)
{
    uint8_t* gdtHelper=(uint8_t*)(&desc::gdt::items[index]);
    *((uint16_t*)(&gdtHelper[0]))=limit&0xFFFF;
    *((uint16_t*)(&gdtHelper[2]))=baseLow&0xFFFF;
    gdtHelper[4]=(baseLow>>16)&0xFF;

    gdtHelper[5]=0x92|((dpl&0x3)<<5)|(code?0x8:0);
    gdtHelper[6]=((limit>>16)&0xF)|(code?0xA0:0xC0);

    gdtHelper[7]=(baseLow>>24)&0xFF;
    *((uint32_t*)(&gdtHelper[8]))=baseHigh;

    *((uint32_t*)(&gdtHelper[12]))=0;
}

static void bzero(char* p,uint32_t size)
{
    uint32_t lwords=size/4;
    uint32_t rest=size%4;
    uint32_t *np=reinterpret_cast<uint32_t*>(p);
    for(;lwords>0;--lwords,++np)
        *np=0;
    p=reinterpret_cast<char*>(np);
    for(;rest>0;--rest,++np)
        *np=0;
}

static void clearFrameBuffer()
{
    bzero(reinterpret_cast<char*>(0xB8000),80*25);
}

static void clearBSS()
{
    bzero(reinterpret_cast<char*>(&bss_start_address),&bss_end_address-&bss_start_address);
}

/*PAE是CR4第5位*/
static void setPAE()
{
    __asm__ __volatile__(
        "mov %cr4,%eax\n"
        "or $0x20, %eax\n"
        "mov %eax,%cr4\n"
    );
}

static void setupKernelPage()
{
    bzero(reinterpret_cast<char*>(kernel::pml4),sizeof(PML4E)*kernel::pml4Size);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(kernel::pdpt),sizeof(PDPTE)*kernel::pdptSize);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(kernel::pdt),sizeof(PDT)*kernel::pdtSize);        //清空内核PML4表
    bzero(reinterpret_cast<char*>(kernel::pt),sizeof(PT)*kernel::ptSize);           //清空内核PML4表
    uint32_t* pml4=reinterpret_cast<uint32_t*>(kernel::pml4);
    uint32_t* pdpt=reinterpret_cast<uint32_t*>(kernel::pdpt);
    uint32_t* pdt=reinterpret_cast<uint32_t*>(kernel::pdt);
    uint32_t* pt=reinterpret_cast<uint32_t*>(kernel::pt);
    for(uint32_t i=0,addr=reinterpret_cast<uint32_t>(pdpt)+0x7;     // 7 表示在内存中、可读、用户可获取
        i<kernel::pdptNum;
        ++i,addr+=pageSize)
    {
        *(pml4)=addr;
        pml4+=2;
    }
    for(uint32_t i=0,addr=reinterpret_cast<uint32_t>(pdt)+0x7;
        i<kernel::pdtNum;
        ++i,addr+=pageSize)
    {
        *(pdpt)=addr;
        pdpt+=2;
    }
    for(uint32_t i=0,addr=reinterpret_cast<uint32_t>(pt)+0x7;
        i<kernel::ptNum;
        ++i,addr+=pageSize)
    {
        *(pdt)=addr;
        pdt+=2;
    }
    
    for(uint32_t i=0,addr=0x7;
        i<kernel::ptSize;
        ++i,addr+=pageSize)
    {
        *(pt)=addr;
        pt+=2;
    }
}

static void enableLongMode()
{
    __asm__ __volatile__(
        "mov $0xC0000080,%ecx\n"
        "rdmsr\n"
        "or $0x900,%eax\n"
        "wrmsr\n"
    );
}

static void setupCR3()
{
    __asm__ __volatile__("mov %[pd],%%cr3" : : [pd]"r"(kernel::pml4));
}

static void enablePaging()
{
    __asm__ __volatile__(
        "mov %cr0,%eax\n"
        "or $0x80000001,%eax\n"
        "mov %eax,%cr0\n"
    );
}


}

__asm__(".code64");
__asm__(".align 8");

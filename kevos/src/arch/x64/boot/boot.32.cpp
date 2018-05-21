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
#include <arch/x64/mem_layout.h>
#include <arch/x64/paging.h>
#include <arch/x64/gdt.h>
#include <arch/x64/vm.h>

#ifdef __KEVOS_MULTIBOOT__
#include <arch/common/multiboot.h>
#endif

KEVOS_NSS_4(kevos,arch,x64,boot);


static_assert(sizeof(uint8_t)==1,"In x86-64 achitecture, uint8_t must be 1 byte!");
static_assert(sizeof(int8_t)==1,"In x86-64 achitecture, int8_t must be 1 bytes!");
static_assert(sizeof(uint16_t)==2,"In x86-64 achitecture, uint16_t must be 2 bytes!");
static_assert(sizeof(int16_t)==2,"In x86-64 achitecture, int16_t must be 2 bytes!");
static_assert(sizeof(uint32_t)==4,"In x86-64 achitecture, uint32_t must be 4 bytes!");
static_assert(sizeof(int32_t)==4,"In x86-64 achitecture, int32_t must be 4 bytes!");
static_assert(sizeof(uint64_t)==8,"In x86-64 achitecture, uint64_t must be 8 bytes!");
static_assert(sizeof(int64_t)==8,"In x86-64 achitecture, int64_t must be 8 bytes!");


static void bzero(char* p,uint32_t size);
static void clearFrameBuffer();
static void clearBSS();
static void setPAE();
static void setup64BitModeGDT();
static void setupKernelPage();
static void enableLongMode();
static void setupCR3();
static void enablePaging();
static void ljmpToEntry64();


extern "C" void entry32()
{
    clearFrameBuffer();     // Done!
    clearBSS();             // Done!
    setupKernelPage();      // Done!
    setPAE();               // Done!
    setupCR3();             // Done!
    enableLongMode();       // Done!
    enablePaging();         // Done!
    // setup64BitModeGDT();
    ljmpToEntry64();
}


static void bzero(char* p,uint32_t size)
{
    uint32_t lwords=size/4;
    uint32_t rest=size%4;
    uint32_t *np=reinterpret_cast<uint32_t*>(p);
    while(lwords--)
        *np++=0;
    p=reinterpret_cast<char*>(np);
    while(rest--)
        *np++=0;
}

static void clearFrameBuffer()
{
    bzero(reinterpret_cast<char*>(0xB8000),80*25);
}

static void clearBSS()
{
    bzero(reinterpret_cast<char*>(&bss_start_address),&bss_end_address-&bss_start_address);
}

static void setup64BitModeGDT()
{
    setGDTEntry(0, 0, 0, 0, 0);                // Null segment
    setGDTEntry(1, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    setGDTEntry(2, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment 
    setGDTEntry(3, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    setGDTEntry(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    struct __packed__
    {
        uint16_t limit;
        uint32_t address;
    } gdtr32;
    gdtr32.limit=sizeof(__knGDT)-1;
    gdtr32.address=reinterpret_cast<uint32_t>(__knGDT);
    __asm__("lgdt %[gdtr]" : : [gdtr]"m"(gdtr32));
    __asmv__(
        "mov %%ax,%%ds\n"
        "mov %%ax,%%es\n"
        "mov %%ax,%%fs\n"
        "mov %%ax,%%gs\n"
        "mov %%ax,%%ss\n"
        : : "a"(__KERNEL_DS)
    );
    __asm__(
        "ljmp %[cs],$__next\n"
        "__next:\n"
        "ret\n"
        : : [cs]"i"(__KERNEL_CS)
    );
}

/*PAE是CR4第5位*/
static void setPAE()
{
    __asmv__(
        "mov %cr4,%eax\n"
        "or $0x20, %eax\n"
        "mov %eax,%cr4\n"
    );
}

static void setupKernelPage()
{
    bzero(reinterpret_cast<char*>(__knPML4),sizeof(PML4E)*__KERNEL_PML4_SIZE);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(__knPDPT),sizeof(PDPTE)*__KERNEL_PDPT_SIZE);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(__knPDT),sizeof(PDT)*__KERNEL_PDT_SIZE);        //清空内核PML4表
    bzero(reinterpret_cast<char*>(__knPT),sizeof(PT)*__KERNEL_PT_SIZE);           //清空内核PML4表
    uint32_t* pml4=reinterpret_cast<uint32_t*>(__knPML4);
    uint32_t* pdpt=reinterpret_cast<uint32_t*>(__knPDPT);
    uint32_t* pdt=reinterpret_cast<uint32_t*>(__knPDT);
    uint32_t* pt=reinterpret_cast<uint32_t*>(__knPT);
    for(uint32_t i=0,addr=reinterpret_cast<uint32_t>(pdpt)+0x3;
        i<__KERNEL_PDPT_NUM;
        ++i,addr+=__PAGE_SIZE)
    {
        *(pml4)=addr;
        pml4+=2;
    }
    for(uint32_t i=0,addr=reinterpret_cast<uint32_t>(pdt)+0x3;
        i<__KERNEL_PDT_NUM;
        ++i,addr+=__PAGE_SIZE)
    {
        *(pdpt)=addr;
        pdpt+=2;
    }
    for(uint32_t i=0,addr=reinterpret_cast<uint32_t>(pt)+0x3;
        i<__KERNEL_PT_NUM;
        ++i,addr+=__PAGE_SIZE)
    {
        *(pdt)=addr;
        pdt+=2;
    }
    for(uint32_t i=0,addr=0x3;
        i<__KERNEL_PT_SIZE;
        ++i,addr+=__PAGE_SIZE)
    {
        *(pt)=addr;
        pt+=2;
    }
}

static void enableLongMode()
{
    __asmv__(
        "mov $0xC0000080,%ecx\n"
        "rdmsr\n"
        "or $0x900,%eax\n"
        "wrmsr\n"
    );
}

static void setupCR3()
{
    asm("mov %[pd],%%cr3" : : [pd]"r"(__knPML4));
}

static void enablePaging()
{
    __asmv__(
        "mov %cr0,%eax\n"
        "or $0x80000001,%eax\n"
        "mov %eax,%cr0\n"
    );
}

static void ljmpToEntry64()
{
    __asmv__("ljmp %[cs],$entry64\n": : [cs]"i"(__KERNEL_CS));
}


KEVOS_NSE_4(x64,arch,kevos,boot);

__asm__(".code64");

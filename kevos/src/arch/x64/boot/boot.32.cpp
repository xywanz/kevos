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


#include <arch/common/arch-conf.h>
#include <arch/x64/descriptor.h>
#include <arch/x64/paging.h>
#include <arch/x64/vm.h>

static_assert(sizeof(uint8_t)==1,"In x86-64 achitecture, uint8_t must be 1 byte!");
static_assert(sizeof(int8_t)==1,"In x86-64 achitecture, int8_t must be 1 bytes!");
static_assert(sizeof(uint16_t)==2,"In x86-64 achitecture, uint16_t must be 2 bytes!");
static_assert(sizeof(int16_t)==2,"In x86-64 achitecture, int16_t must be 2 bytes!");
static_assert(sizeof(uint32_t)==4,"In x86-64 achitecture, uint32_t must be 4 bytes!");
static_assert(sizeof(int32_t)==4,"In x86-64 achitecture, int32_t must be 4 bytes!");
static_assert(sizeof(uint64_t)==8,"In x86-64 achitecture, uint64_t must be 8 bytes!");
static_assert(sizeof(int64_t)==8,"In x86-64 achitecture, int64_t must be 8 bytes!");

#ifdef __KEVOS_MULTIBOOT__

#include <arch/common/multiboot.h>

#define __MAGIC ((uint32_t)MULTIBOOT_MAGIC)
#define __FLAGS ((uint32_t)MULTIBOOT_PAGE_ALIGNED|MULTIBOOT_MEMORY_INFO)
#define __CHECKSUM ((uint32_t)(-(__MAGIC+__FLAGS)))

__section__(".boot")
static constexpr MultibootHeaderBase multibootHeader =
{
    __MAGIC,
    __FLAGS,
    __CHECKSUM
};

#endif

SegmentDescriptor __knGDT[5];

struct __packed__ GDTR32
{
    uint16_t limit;
    uint32_t address;
};

extern uint32_t kernel_start_address;
extern uint32_t bss_start_address;
extern uint32_t bss_end_address;
extern PML4E __knPML4[];
extern PDPT  __knPDPT[];
extern PDT   __knPDT[];
extern PT    __knPT[];

static void bzero(char* p,uint32_t size);
static void setSegmentDescriptor(SegmentDescriptor* _pDesc,uint8_t _isCode);
static void setSystemDescriptor(SystemDescriptor* _pDesc,uint8_t _isCode);
static inline void clearFrameBuffer();
static inline void clearBSS();
static inline void setPAE();
static inline void setup64BitModeGDT();
static inline void setupKernelPage();
static inline void enableLongMode();
static inline void setupCR3();
static inline void enablePaging();
static inline void ljmpToEntry64();


extern "C" void entry32()
{
    clearFrameBuffer();     // Done!
    clearBSS();             // Done!
    setupKernelPage();      // Done!
    setPAE();               // Done!
    setupCR3();             // Done!
    enableLongMode();       // Done!
    enablePaging();         // Done!
    setup64BitModeGDT();
    ljmpToEntry64();
}


void bzero(char* p,uint32_t size)
{
    uint32_t lwords=size/4;
    uint32_t rest=size%4;
    uint32_t *np=(uint32_t*)p;
    while(lwords--)
        *np++=0;
    p=(char*)np;
    while(rest--)
        *np++=0;
}

void setSegmentDescriptor(SegmentDescriptor* _pDesc,uint8_t _isCode)
{
    _pDesc->limitLow=0xFFFF;
    _pDesc->limitHigh=0xF;
    _pDesc->baseLow=0;
    _pDesc->baseHigh=0;
    _pDesc->p=1;
    _pDesc->l=1;
    _pDesc->g=1;
    _pDesc->s=1;
    _pDesc->avl=0;
    _pDesc->dpl=0;
    if(_isCode)
        _pDesc->type=0x8;
    else
        _pDesc->type=0x0;
}

void setSystemDescriptor(SystemDescriptor* _pDesc,uint8_t _isCode)
{
    _pDesc->limitLow=0xFFFF;
    _pDesc->limitHigh=0xF;
    _pDesc->baseLow=0;
    _pDesc->baseHigh=0;
    _pDesc->baseHigh32=0;
    _pDesc->reserved=0;
    _pDesc->p=1;
    _pDesc->l=1;
    _pDesc->g=1;
    _pDesc->s=0;
    _pDesc->avl=0;
    _pDesc->dpl=0;
    if(_isCode)
        _pDesc->type=0x8;
    else
        _pDesc->type=0x0;
}

void clearFrameBuffer()
{
    bzero((char*)0xB8000,80*25);
}

void clearBSS()
{
    bzero((char*)&bss_start_address,&bss_end_address-&bss_start_address);
}

void setup64BitModeGDT()
{
    bzero((char*)__knGDT,sizeof(__knGDT[0]));    //GDT[0] 空GDT
    setSegmentDescriptor(__knGDT+1,0);  //GDT[1] 内核数据段 
    setSegmentDescriptor(__knGDT+2,1);  //GDT[2] 内核代码段
    GDTR32 gdtr32;
    gdtr32.limit=sizeof(__knGDT)-1;
    gdtr32.address=(uint32_t)__knGDT;
    __asm__("lgdt %[gdtr]" : : [gdtr]"m"(gdtr32));
    __asm__(
        "ljmp %[cs],$__next\n"
        "__next:\n"
        : : [cs]"i"(__KERNEL_CS)
    );
    __asmv__(
        "mov %%ax,%%ds\n"
        "mov %%ax,%%es\n"
        "mov %%ax,%%fs\n"
        "mov %%ax,%%gs\n"
        "mov %%ax,%%ss\n"
        : : "a"(__KERNEL_DS)
    );
}

/*PAE是CR4第5位*/
void setPAE()
{
    __asmv__(
        "mov %cr4,%eax\n"
        "or $0x20, %eax\n"
        "mov %eax,%cr4\n"
    );
}

void setupKernelPage()
{
    bzero(reinterpret_cast<char*>(__knPML4),sizeof(PML4E)*KERNEL_PML4_SIZE);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(__knPDPT),sizeof(PDPTE)*KERNEL_PDPT_SIZE);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(__knPDT),sizeof(PDT)*KERNEL_PDT_SIZE);    //清空内核PML4表
    bzero(reinterpret_cast<char*>(__knPT),sizeof(PT)*KERNEL_PT_SIZE);    //清空内核PML4表
    *reinterpret_cast<uint32_t*>(__knPML4)=reinterpret_cast<uint32_t>(__knPDPT)+0x3;
    *reinterpret_cast<uint32_t*>(__knPDPT)=reinterpret_cast<uint32_t>(__knPDT)+0x3;
    *reinterpret_cast<uint32_t*>(__knPDT)=reinterpret_cast<uint32_t>(__knPT)+0x3;
    *reinterpret_cast<uint32_t*>(__knPDT+2)=reinterpret_cast<uint32_t>(__knPT)+0x1000+0x3;
    *reinterpret_cast<uint32_t*>(__knPDT+4)=reinterpret_cast<uint32_t>(__knPT)+0x2000+0x3;
    *reinterpret_cast<uint32_t*>(__knPDT+6)=reinterpret_cast<uint32_t>(__knPT)+0x3000+0x3;
    *reinterpret_cast<uint32_t*>(__knPDT+8)=reinterpret_cast<uint32_t>(__knPT)+0x4000+0x3;
    *reinterpret_cast<uint32_t*>(__knPDT+10)=reinterpret_cast<uint32_t>(__knPT)+0x5000+0x3;
    uint32_t addr=0x3;
    uint32_t* pt=reinterpret_cast<uint32_t*>(__knPT);
    for(uint32_t i=0;i<KERNEL_PT_SIZE;++i)
    {
        *pt=addr;
        pt+=2;
        addr+=PAGE_SIZE;
    }
}

void enableLongMode()
{
    __asmv__(
        "mov $0xC0000080,%ecx\n"
        "rdmsr\n"
        "or $0x900,%eax\n"
        "wrmsr\n"
    );
}

void setupCR3()
{
    asm("mov %[pd],%%cr3" : : [pd]"r"(__knPML4));
}

void enablePaging()
{
    __asmv__(
        "mov %cr0,%eax\n"
        "or $0x80000001,%eax\n"
        "mov %eax,%cr0\n"
    );
}

void ljmpToEntry64()
{
    __asmv__("ljmp %[cs],$entry64\n": : [cs]"i"(__KERNEL_CS));
}


__asm__(".code64");

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

extern uint32_t bss_start_address;
extern uint32_t bss_end_address;
extern PML4E __knPML4[];
extern PDPT  __knPDPT[];
extern PDT   __knPDT[];
extern PT    __knPT[];

static void bzero(char* p,uint32_t size);
static void setSegmentDescriptor(SegmentDescriptor* _pDesc,uint32_t _base,uint32_t _limit,
        uint8_t _dpl,uint8_t _code,uint8_t _longMode);
static inline void setPAE();
static inline void initGDT();
static inline void initKernelPage();
static inline void enablePaging();


extern "C" void entry32()
{
    bzero((char*)0xB8000,80*25);
    bzero((char*)&bss_start_address,&bss_end_address-&bss_start_address);
    initKernelPage();
	while(1){};
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

void setSegmentDescriptor(SegmentDescriptor* _pDesc,uint32_t _base,uint32_t _limit,
        uint8_t _dpl,uint8_t _code,uint8_t _longMode)
{
    _pDesc->baseLow=_base&0xFFFFFF;
    _pDesc->baseHigh=_base>>24;
    _pDesc->limitLow=_limit&0xFFFF;
    _pDesc->limitHigh=(_limit>>16)&0xF;
    _pDesc->mustOne=1;
    _pDesc->dpl=_dpl;
    _pDesc->avl=0;
    _pDesc->longMode=_longMode;
}

void initGDT()
{
    __asmv__(
        "mov $0x10,%ax\n"
        "mov %ax,%ds\n"
        "mov %ax,%es\n"
        "mov %ax,%fs\n"
        "mov %ax,%gs\n"
        "mov %ax,%ss"
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

static inline void initKernelPage()
{
    bzero(reinterpret_cast<char*>(__knPML4),0x1000);
}

void enablePaging()
{
    __asmv__(
        "mov %cr0,%eax\n"
        "or $0x80000001,%eax\n"
        "mov %eax,%cr0\n"
    );
}


__asm__(".code64");

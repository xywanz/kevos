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

  这段代码只能使用32位及以下的整形
*/

/*此段代码编译成32位代码，4字节对齐
*/
__asm__(".code32");
__asm__(".align 4");
__asm__(".equ VIRTUAL_START_ADDRESS,0xFFFFFFFF80000000");


#include <arch/common/arch-conf.h> 
#include <arch/common/multiboot.h>
#include <arch/x64/descriptor.h>
#include <arch/x64/paging.h>


#define V2P(x) (char*)(((uint32_t)(((char*)x)+0x7FFFFFFF))+1)
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
static void setSegmentDescriptor(SegmentDescriptor* _pDesc,uint32_t _baseHigh,uint32_t _baseLow,
                        uint32_t _limit,uint8_t _dpl,uint8_t _code,uint8_t _tss);
static inline void initializeBootTimePage();


extern "C" void entry32()
{
    bzero((char*)0xB8000,80*25);
    bzero(V2P(&bss_start_address),V2P(&bss_end_address)-V2P(&bss_start_address));
    //initializeBootTimePage();
    __asm__("mov %cr4,%eax\n"
            "or $0x20, %eax\n"
            "mov %eax,%cr4\n");
    __asm__("mov %[pd],%%cr3" : : [pd]"r"(V2P(__knPML4)));
    __asm__("mov $0xC0000080,%ecx\n"
            "rdmsr\n"
            "or $0x900,%eax\n"
            "wrmsr\n");
    __asm__("push $2\n"
            "popf\n");
    __asm__("mov %cr0,%eax\n"
            "or $0x80000001,%eax\n"
            "mov %eax,%cr0\n");
    // SegmentDescriptor* pGDT=(SegmentDescriptor*)V2P(__knGDT);
    // setSegmentDescriptor(pGDT+1, 0, 0, 0, 0, 1, 0);
    // setSegmentDescriptor(pGDT+2, 0, 0, 0, 0, 0, 0);
    // setSegmentDescriptor(pGDT+3, 0, 0, 0, 3, 1, 0);
    // // setSegmentDescriptor(pGDT+4, 0, 0, 0, 3, 0, 0);
    // GDTR32 gdtr32;
    // gdtr32.limit = sizeof(__knGDT) - 1;
    // gdtr32.address = (uint32_t)V2P(__knGDT);
    // __asm__("lgdt %[gdtr]" : : [gdtr]"m"(gdtr32));
    // __asm__("mov %%ax, %%ds\n"
    //         "mov %%ax, %%es\n"
    //         "mov %%ax, %%ss\n"
    //         "mov %%ax, %%fs\n"
    //         "mov %%ax, %%gs\n"
    //         : : "a"(16));
    // __asm__("ljmp %[cs],$entry64-VIRTUAL_START_ADDRESS\n" : : [cs]"i"(24));
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

void setSegmentDescriptor(SegmentDescriptor* _pDesc,uint32_t _baseHigh,uint32_t _baseLow,
                        uint32_t _limit,uint8_t _dpl,uint8_t _code,uint8_t _tss)
{
    _pDesc->baseLowLow=(uint16_t)(_baseLow&0xFFFF);
    _pDesc->baseLowMid=(uint8_t)((_baseLow>>16)&0xFF);
    _pDesc->baseLowHigh=(uint8_t)((_baseLow>>24)&0xFF);
    _pDesc->baseHigh=_baseHigh;
    _pDesc->limitLow=(uint16_t)(_limit&0xFFFF);
    _pDesc->limitHigh=(uint8_t)((_limit>>16)&0xF);
    _pDesc->attrLow=(_tss?0x89:0x92)|((_dpl&0x3)<<5)|(_code?0x8:0);
    _pDesc->attrHigh=_code?0xA:0xC;
}

void initializeBootTimePage()
{
    __asm__("movl $__knPDPT-VIRTUAL_START_ADDRESS+3,__knPML4-VIRTUAL_START_ADDRESS\n"
            "movl $0,__knPML4-VIRTUAL_START_ADDRESS+4\n");
    __asm__("movl $__knPDT-VIRTUAL_START_ADDRESS+3,__knPDPT-VIRTUAL_START_ADDRESS\n"
            "movl $0,__knPDPT-VIRTUAL_START_ADDRESS+4\n");
    __asm__("movl $0x83, __knPDT-VIRTUAL_START_ADDRESS\n"
            "movl $0, __knPDT-VIRTUAL_START_ADDRESS+4\n");
}


__asm__(".code64");

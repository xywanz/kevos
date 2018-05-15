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


#include <arch/common/arch-conf.h> 
#include <arch/common/multiboot.h>
#include <arch/x64/descriptor.h>
#include <sys/portable.h>


#define V2P(x) (uint8_t*)(((uint32_t)(((uint8_t*)x)+0x7FFFFFFF))+1)
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

struct __packed__ GDTR32
{
    uint16_t limit;
    uint32_t address;
};

void setSegDescriptor(SegDescriptor* _pDesc,uint32_t _baseHigh,uint32_t _baseLow,
                        uint32_t _limit,uint8_t _dpl,uint8_t _code,uint8_t _tss);


extern "C" void entry32()
{
    // asm("movl $0xB8000,%eax");
    // asm("movb $75,0(%eax)");
    // asm("movb $75,1(%eax)");
	while(1){};
}


void setSegDescriptor(SegDescriptor* _pDesc,uint32_t _baseHigh,uint32_t _baseLow,
                    uint32_t _limit,uint8_t _dpl,bool _code,bool _tss)
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

__asm__(".code64");

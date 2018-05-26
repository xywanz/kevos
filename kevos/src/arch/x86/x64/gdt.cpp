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

#include <arch/x86/x64/gdt.h>

KEVOS_NSS_3(arch,x86,x64);

static void setSystemDescriptor(uint32_t index,uint32_t baseHigh,uint32_t baseLow,
            uint32_t limit,uint8_t dpl,uint8_t code,uint8_t tss)
{
    uint8_t* gdtHelper=(uint8_t*)(&GDT::items[index]);
    *((uint16_t*)(&gdtHelper[0]))=limit&0xFFFF;
    *((uint16_t*)(&gdtHelper[2]))=baseLow&0xFFFF;
    gdtHelper[4]=(baseLow>>16)&0xFF;

    gdtHelper[5]=(tss?0x89:0x92)|((dpl&0x3)<<5)|(code?0x8:0);
    gdtHelper[6]=((limit>>16)&0xF)|(code?0xA0:0xC0);

    gdtHelper[7]=(baseLow>>24)&0xFF;
    *((uint32_t*)(&gdtHelper[8]))=baseHigh;

    *((uint32_t*)(&gdtHelper[12]))=0;
}

void GDT::setItem(uint32_t index,uint32_t baseHigh,uint32_t baseLow,
            	uint32_t limit,uint8_t dpl,uint8_t code,uint8_t tss)
{
	if(index>=gdtSize)
		return;
	setSystemDescriptor(index,baseHigh,baseLow,limit,dpl,code,tss);
}

void GDT::load()
{
	struct __packed__ GDTPointer
    {
        uint16_t limit;
        uint64_t address;
    } gdtPtr;
    gdtPtr.limit=sizeof(GDT::items)-1;
    gdtPtr.address=reinterpret_cast<uint64_t>(GDT::items);
    __asm__("lgdt %[gdtr]" : : [gdtr]"m"(gdtPtr));
}

SystemDescriptor GDT::items[gdtSize];

KEVOS_NSE_3(x64,x86,arch);

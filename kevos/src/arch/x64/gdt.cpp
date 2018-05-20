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

#include <arch/x64/gdt.h>

KEVOS_NSS_3(kevos,arch,x64);


SegmentDescriptor __knGDT[__GDT_SIZE];

struct SegmentHelper
{
   uint16_t limitLow;           // The lower 16 bits of the limit.
   uint16_t baseLow;            // The lower 16 bits of the base.
   uint8_t  baseMiddle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  baseHigh;           // The last 8 bits of the base.
};

void setGDTEntry(uint32_t index,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran)
{
	SegmentHelper* helper=reinterpret_cast<SegmentHelper*>(__knGDT+index);
	helper->baseLow=base&0xFFFF;
	helper->baseMiddle=(base>>16)&0xFF;
	helper->baseHigh=(base>>24)&0xFF;
	helper->limitLow=limit&0xFFFF;
	helper->granularity=(limit>>16)&0x0F;
	helper->granularity|=gran&0xF0;
	helper->access=access;
	
}


KEVOS_NSE_3(x64,arch,kevos);

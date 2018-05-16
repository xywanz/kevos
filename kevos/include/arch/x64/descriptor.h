
#ifndef _KEVOS_ARCH_X64_DESCRIPTOR_H_
#define _KEVOS_ARCH_X64_DESCRIPTOR_H_


#include <arch/x64/types.h>


struct __packed__ SegmentDescriptor
{
	uint16_t   limitLow;
    uint16_t   baseLowLow;
	uint8_t    baseLowMid;
    uint8_t    attrLow;
    uint8_t    limitHigh    :   4;
    uint8_t    attrHigh     :   4;
    uint8_t    baseLowHigh;
    uint32_t   baseHigh;
    uint32_t   reserve;
};


#endif
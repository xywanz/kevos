
#ifndef _KEVOS_ARCH_X64_DESCRIPTOR_H_
#define _KEVOS_ARCH_X64_DESCRIPTOR_H_


#include <arch/x64/types.h>

/*
    系统GDT 16字节，代码和数据的GDT 8字节
    64位模式下屏蔽了段寻址，但仍然用段来控制一些属性，如长模式或是兼容模式
*/
struct __packed__ SegmentDescriptor
{
	uint64_t	limitLow 	:	16;
    uint64_t   	baseLow 	:	24;
    uint64_t   	type 		:	4;
    uint64_t   	mustOne    	:   1;
    uint64_t   	dpl     	:   2;
    uint64_t   	present		:	1;
    uint64_t	limitHigh	:	4;
    uint64_t    avl			:	1;
    uint64_t   	longMode	:	1;
    uint64_t	big 		:	1;
    uint64_t   	granularity	:	1;       //粒度
    uint64_t	baseHigh	:	8;
};


#endif
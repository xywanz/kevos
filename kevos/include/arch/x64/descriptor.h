
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
    // uint64_t    typeA       :   1;      // accessed，访问过置1
    // uint64_t    typeRW      :   1;      // W/R，可写置1
    // uint64_t    typeEDC     :   1;      // ED/C，数据段置1表示向下扩展，代码段置1表示遵循描述符优先级
    // uint64_t    typeE       :   1;      // E，置1表示代码段，0表示数据段
    uint64_t   	s           :   1;         // S，置1表示系统段描述符，扩展为16字节
    uint64_t   	dpl     	:   2;
    uint64_t   	present		:	1;
    uint64_t	limitHigh	:	4;
    uint64_t    avl			:	1;         // AVL，系统软件可自由使用的位
    uint64_t   	longMode	:	1;
    uint64_t	db 		    :   1;
    uint64_t   	g	        :	1;       //粒度
    uint64_t	baseHigh	:	8;
};

#define SEGMENT_DATA_R          0x0
#define SEGMENT_DATA_RW         0x2
#define SEGMENT_DATA_RED        0x4
#define SEGMENT_DATA_RWED       0x6
#define SEGMENT_CODE_X          0x8
#define SEGMENT_CODE_XR         0xA
#define SEGMENT_CODE_XC         0xC
#define SEGMENT_CODE_XRC        0xE

#define KERNEL_DS               0x08
#define KERNEL_CS               0x10


#endif

#ifndef _KEVOS_ARCH_X64_DESCRIPTOR_H_
#define _KEVOS_ARCH_X64_DESCRIPTOR_H_

#include <arch/x64/types.h>

#define __SEGMENT_DATA_R          0x0
#define __SEGMENT_DATA_RW         0x2
#define __SEGMENT_DATA_RED        0x4
#define __SEGMENT_DATA_RWED       0x6
#define __SEGMENT_CODE_X          0x8
#define __SEGMENT_CODE_XR         0xA
#define __SEGMENT_CODE_XC         0xC
#define __SEGMENT_CODE_XRC        0xE

#define __KERNEL_DS               0x08
#define __KERNEL_CS               0x10

KEVOS_NSS_3(kevos,arch,x64);

/*
    段描述符

    段寻址分为两种模式，一种是在32为兼容（compatibility）模式下，另一种是在64位长模式下。

    兼容模式：
    * 段寻址方式和x86架构相同，段所代表的含义与x86架构相同。
    * 各个位的详细说明可参考下方UserSegmentDescriptor的描述。

    长模式代码段：
    * 代码段的C、L、D、P、DPL位有效，Base强制为0，Limit无效。
    * S、C/D位虽然无效，但必须为1。R、A无效，代码段强制为可读。
    * C位表示代码是否遵循优先级，D表示代码的操作位数，P表示是否在内存中，L表示是否是长模式代码段。

    长模式数据段：
    * S和C/D虽然无效，但必须S=1，C/D=0。
    * 对于加载到DS、ES、SS的段描述符来说，属性位只有P位有效。
    * 对于加载到FS、GS的段描述符来说，Base有效。
*7

/*
    64位模式下屏蔽了段寻址，但仍然用段来控制一些属性
    
    段描述符用于对寻址进行限制
*/
struct __packed__ SegmentDescriptor
{
	uint64_t	limitLow 	:	16;
    uint64_t   	baseLow 	:	24;
    uint64_t   	type 		:	4;
    // uint64_t    typeA       :   1;      // A位，accessed，访问过置1
    // uint64_t    typeRW      :   1;      // W/R位，可写置1
    // uint64_t    typeEDC     :   1;      // ED/C位，数据段置1表示向下扩展，代码段置1表示遵循描述符优先级
    // uint64_t    typeCD      :   1;      // C/D位，置1表示代码段，0表示数据段
    uint64_t   	s           :   1;         // S位，置1表示用户段描述符
    uint64_t   	dpl     	:   2;
    uint64_t   	p		    :	1;         // P位，present，表示段是否在内存中
    uint64_t	limitHigh	:	4;
    uint64_t    avl			:	1;         // AVL位，系统软件可自由使用的位
    uint64_t   	l	        :	1;         // L位
    uint64_t	d 		    :   1;         // D位，default operand size
    uint64_t   	g	        :	1;         // G位，粒度
    uint64_t	baseHigh	:	8;
};

/*
    系统描述符

    包括系统段描述符及门描述符，为了区分系统描述符和段描述符，系统描述符的S位置0且高64位的type所有位置0
*/
struct __packed__ SystemDescriptor
{
    uint64_t    limitLow    :   16;
    uint64_t    baseLow     :   24;
    uint64_t    type        :   4;
    // uint64_t    typeA       :   1;      // A位，accessed，访问过置1
    // uint64_t    typeRW      :   1;      // W/R位，可写置1
    // uint64_t    typeEDC     :   1;      // ED/C位，数据段置1表示向下扩展，代码段置1表示遵循描述符优先级
    // uint64_t    typeCD      :   1;      // C/D位，置1表示代码段，0表示数据段
    uint64_t    s           :   1;         // S位，置1表示用户段描述符
    uint64_t    dpl         :   2;
    uint64_t    p           :   1;         // P位，present，表示段是否在内存中
    uint64_t    limitHigh   :   4;
    uint64_t    avl         :   1;         // AVL位，系统软件可自由使用的位
    uint64_t    l           :   1;         // L位
    uint64_t    d           :   1;         // D位，default operand size
    uint64_t    g           :   1;         // G位，粒度
    uint64_t    baseHigh    :   8;
    
    uint64_t    baseHigh32  :   32;
    uint64_t    reserved    :   32;
};


KEVOS_NSE_3(x64,arch,kevos);

#endif

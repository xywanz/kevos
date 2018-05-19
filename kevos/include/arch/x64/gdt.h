
#ifndef _KEVOS_ARCH_X64_GDT_H_
#define _KEVOS_ARCH_X64_GDT_H_

#include <arch/x64/descriptor.h>

#define __GDT_SIZE	5

KEVOS_NSS_3(kevos,arch,x64);


extern SegmentDescriptor __knGDT[__GDT_SIZE];


KEVOS_NSE_3(x64,arch,kevos);

#endif
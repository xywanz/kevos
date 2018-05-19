
#include <arch/x64/gdt.h>

KEVOS_NSS_3(kevos,arch,x64);


SegmentDescriptor __knGDT[__GDT_SIZE];


KEVOS_NSE_3(x64,arch,kevos);

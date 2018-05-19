
#ifndef _KEVOS_ARCH_X64_MEM_LAYOUT_H_
#define _KEVOS_ARCH_X64_MEM_LAYOUT_H_

#include <sys/portable.h>
#include <arch/x64/types.h>

KEVOS_NSS_3(kevos,arch,x64);


extern "C" uint64_t text_start_address;
extern "C" uint64_t text_end_address;

extern "C" uint64_t data_start_address;
extern "C" uint64_t data_end_address;

extern "C" uint64_t bss_start_address;
extern "C" uint64_t bss_end_address;


KEVOS_NSE_3(x64,arch,kevos);

#endif

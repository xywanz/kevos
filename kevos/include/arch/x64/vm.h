
#ifndef _KEVOS_ARCH_X64_VM_H_
#define _KEVOS_ARCH_X64_VM_H_

#include <arch/x64/paging.h>

#define KERNEL_PML4_SIZE		(PML4_SIZE)
#define KERNEL_PDPT_SIZE		(2*PDPT_SIZE)
#define KERNEL_PDT_SIZE 		(2*PDT_SIZE)
#define KERNEL_PT_SIZE 			(8*PT_SIZE)

KEVOS_NSS_3(kevos,arch,x64);


extern PML4E __knPML4[KERNEL_PML4_SIZE];
extern PDPTE __knPDPT[KERNEL_PDPT_SIZE];
extern PDTE  __knPDT[KERNEL_PDT_SIZE];
extern PTE   __knPT[KERNEL_PT_SIZE];


KEVOS_NSE_3(x64,arch,kevos);

#endif

#ifndef _KEVOS_ARCH_X64_PAGING_H_
#define _KEVOS_ARCH_X64_PAGING_H_

#include <sys/portable.h>
#include <arch/x64/types.h>


struct __packed__ PML4E
{
	uint64_t present			:	1;
	uint64_t writable			:	1;
	uint64_t userAccessable		:	1;
	uint64_t writeThrough		:	1;
	uint64_t cacheDisabled		:	1;
	uint64_t ignored1			:	1;
	uint64_t size				:	1;
	uint64_t ignored2			:	4;
	uint64_t physicalPageNum	:	28;
	uint64_t reserved1			:	12;
	uint64_t ignored3			:	11;
	uint64_t executionDisabled	:	1;
};

struct __packed__ PDPTE
{
	uint64_t present			:	1;
	uint64_t writable			:	1;
	uint64_t userAccessable		:	1;
	uint64_t writeThrough		:	1;
	uint64_t cacheDisabled		:	1;
	uint64_t ignored1			:	1;
	uint64_t size				:	1;
	uint64_t ignored2			:	4;
	uint64_t physicalPageNum	:	28;
	uint64_t reserved1			:	12;
	uint64_t ignored3			:	11;
	uint64_t executionDisabled	:	1;
};

struct __packed__ PDTE
{
	uint64_t present			:	1;
	uint64_t writable			:	1;
	uint64_t userAccessable		:	1;
	uint64_t writeThrough		:	1;
	uint64_t cacheDisabled		:	1;
	uint64_t ignored1			:	1;
	uint64_t size				:	1;
	uint64_t ignored2			:	4;
	uint64_t physicalPageNum	:	28;
	uint64_t reserved1			:	12;
	uint64_t ignored3			:	11;
	uint64_t executionDisabled	:	1;
};

struct __packed__ PTE
{
	uint64_t present			:	1;
	uint64_t writable			:	1;
	uint64_t userAccessable		:	1;
	uint64_t writeThrough		:	1;
	uint64_t cacheDisabled		:	1;
	uint64_t accessed			:	1;
	uint64_t dirty				:	1;
	uint64_t size				:	1;
	uint64_t ignored1			:	3;
	uint64_t physicalPageNum	:	28;
	uint64_t reserved1			:	12;
	uint64_t ignored2			:	11;
	uint64_t executionDisabled	:	1;
};


#define PML4_SIZE 		512
#define PDPT_SIZE		512
#define PDT_SIZE 		512
#define PT_SIZE 		512
#define PAGE_SIZE		4096

using PML4=PML4E[PML4_SIZE];
using PDPT=PDPTE[PDPT_SIZE];
using PDT=PDTE[PDT_SIZE];
using PT=PTE[PT_SIZE];


#endif
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

/*****************************************************************************
*  @file     paging.h                            
*  @brief    分页项结构                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_64_X64_PAGING_H_
#define _KEVOS_ARCH_x86_64_X64_PAGING_H_

#include <sys/portable.h>
#include <arch/common/types.h>

#define __PML4_SIZE 		512
#define __PDPT_SIZE			512
#define __PDT_SIZE 			512
#define __PT_SIZE 			512
#define __PAGE_SIZE			4096

KEVOS_NSS_4(kevos,arch,x86_64,x64);


struct __packed__ PML4E
{
	uint64_t present			:	1;
	uint64_t writable			:	1;
	uint64_t userAccessable		:	1;
	uint64_t writeThrough		:	1;
	uint64_t cacheDisabled		:	1;
	uint64_t accessed           :	1;
	uint64_t ignored1			:	1;
	uint64_t size				:	1;
	uint64_t ignored2			:	4;
	uint64_t physicalPageNum	:	36;
	uint64_t reserved1			:	4;
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
	uint64_t accessed           :	1;
	uint64_t ignored1			:	1;
	uint64_t size				:	1;
	uint64_t ignored2			:	4;
	uint64_t physicalPageNum	:	36;
	uint64_t reserved1			:	4;
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
	uint64_t accessed           :	1;
	uint64_t ignored1			:	1;
	uint64_t size				:	1;
	uint64_t ignored2			:	4;
	uint64_t physicalPageNum	:	36;
	uint64_t reserved1			:	4;
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
	uint64_t global				:	1;
	uint64_t ignored1			:	3;
	uint64_t physicalPageNum	:	36;
	uint64_t reserved1			:	4;
	uint64_t ignored2			:	11;
	uint64_t executionDisabled	:	1;
};

using PML4=PML4E[__PML4_SIZE];
using PDPT=PDPTE[__PDPT_SIZE];
using PDT=PDTE[__PDT_SIZE];
using PT=PTE[__PT_SIZE];


KEVOS_NSE_4(x64,x86_64,arch,kevos);

#endif

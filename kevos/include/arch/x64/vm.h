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
*  @file     vm.h                            
*  @brief    虚拟内存管理模块                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_X64_VM_H_
#define _KEVOS_ARCH_X64_VM_H_

#include <arch/x64/paging.h>

/**
 * @brief 内核中各分页结构表的大小
 */
#define __KERNEL_PML4_NUM			1
#define __KERNEL_PDPT_NUM			1
#define __KERNEL_PDT_NUM 			1
#define __KERNEL_PT_NUM 			16

/**
 * @brief 内核中各分页结构表项的数量
 */
#define __KERNEL_PML4_SIZE			(__KERNEL_PML4_NUM*__PML4_SIZE)
#define __KERNEL_PDPT_SIZE			(__KERNEL_PDPT_NUM*__PDPT_SIZE)
#define __KERNEL_PDT_SIZE 			(__KERNEL_PDT_NUM*__PDT_SIZE)
#define __KERNEL_PT_SIZE 			(__KERNEL_PT_NUM*__PT_SIZE)


KEVOS_NSS_3(kevos,arch,x64);


/**
 * @brief 内核态的分页结构表
 */
extern PML4E __knPML4[__KERNEL_PML4_SIZE];
extern PDPTE __knPDPT[__KERNEL_PDPT_SIZE];
extern PDTE  __knPDT [__KERNEL_PDT_SIZE];
extern PTE   __knPT  [__KERNEL_PT_SIZE];


/**
 * @brief 一个虚拟内存页的映射信息
 */
struct VMemMap
{
	PML4E*  pml4;
	PDPTE*  pdpt;
	PDTE*	pdt;
	PTE*	pt;

	uint64_t pml4PPN;
	uint64_t pdptPPN;
	uint64_t pdtPPN;
	uint64_t ptPPN;

	uint64_t pageSize;

	uint64_t pml4Index;
	uint64_t pdptIndex;
	uint64_t pdtIndex;
	uint64_t ptIndex;		
};


/**
 * @brief 虚拟内存的抽象，表示一个完整的虚拟内存
 */
class VirtualMemory
{
public:
	VirtualMemory();

	~VirtualMemory();

/**
 * @brief 将物理页面映射到虚拟页面
 *
 * @param vPagePPN 		虚拟页面号
 * @param pPagePPN 		物理页面号
 * @param userAccess	用户态可访问
 * @param pageSize 		页面大小
 * @return				是否成功映射		
 */
	bool mapPage(uint64_t vPagePPN,uint64_t pPagePPN,uint64_t userAccessable,uint64_t pageSize=__PAGE_SIZE);

/**
 * @brief 将虚拟页面的映射取消
 *
 * @param vPagePPN 		虚拟页面号
 * @return				是否成功取消映射		
 */
	bool unmapPage(uint64_t vPagePPN);

/**
 * @brief 计算页面号为ppn的页面的地址，可以是虚拟页面号也可以是物理页面号
 *
 * @param ppn 		页面号
 * @param pageSize 	页面大小，默认值为系统所使用的页面大小
 * @return			页面号为ppn的页面的物理地址
 */
	static uint64_t getAddressFromPPN(uint64_t ppn,uint64_t pageSize=__PAGE_SIZE)
	{
		return ppn*pageSize;
	}

/**
 * @brief 该函数用于解析虚拟页面号在PML4下的映射信息，暂时只支持计算4KB页面
 *
 * @param pml4PPN 	虚拟页面所在的PML4的物理页面号
 * @param vPagePPN	虚拟页面的页面号
 * @return 			VMemMap结构，包含虚拟地址所在的页面结构表项地址、页面号、索引以及页面大小
 */
	static VMemMap resolveMap(uint64_t pml4PPN,uint64_t vPagePPN);

/**
 * @brief 该函数用于解析虚拟页面号在类实例中的PML4下的映射信息，暂时只支持计算4KB页面
 *
 * @param vPagePPN	虚拟页面的页面号
 * @return 			VMemMap结构，包含虚拟地址所在的页面结构表项地址、页面号、索引以及页面大小
 */
	VMemMap resolveMap(uint64_t vPagePPN)
	{
		return resolveMap(m_pml4PPN,vPagePPN);
	}

private:

/**
 * @brief 管理PML4的物理页面号，代表了整个虚拟内存
 */
	uint64_t m_pml4PPN;
	
};


KEVOS_NSE_3(x64,arch,kevos);

#endif
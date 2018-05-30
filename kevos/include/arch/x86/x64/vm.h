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

#ifndef _KEVOS_ARCH_x86_X64_VM_H_
#define _KEVOS_ARCH_x86_X64_VM_H_

#include <arch/x86/x64/paging.h>

KEVOS_NSS_3(arch,x86,x64);

/**
 * @brief 内核中各分页结构表的大小
 */
#define __KERNEL_PML4_NUM			1
#define __KERNEL_PDPT_NUM			1
#define __KERNEL_PDT_NUM 			1
#define __KERNEL_PT_NUM 			32

/**
 * @brief 内核中各分页结构表项的数量
 */
#define __KERNEL_PML4_SIZE			(__KERNEL_PML4_NUM*__PML4_SIZE)
#define __KERNEL_PDPT_SIZE			(__KERNEL_PDPT_NUM*__PDPT_SIZE)
#define __KERNEL_PDT_SIZE 			(__KERNEL_PDT_NUM*__PDT_SIZE)
#define __KERNEL_PT_SIZE 			(__KERNEL_PT_NUM*__PT_SIZE)

/**
 * @brief 内核态的分页结构表
 */

class KernelPageFrame
{
public:
	constexpr static size_t pml4Size = 512;
	constexpr static size_t pdptSize = 512;
	constexpr static size_t pdtSize = 512;
	constexpr static size_t ptSize = 512*32;

	static PML4E  pml4[];
	static PDPTE  pdpt[];
	static PDTE   pdt[];
	static PTE    pt[];
};

/**
 * @brief 一个虚拟内存页的映射信息
 */
struct __packed__ VMemMap
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
 * @param vpn 			虚拟页面号
 * @param ppn 			物理页面号
 * @param userAccess	用户态可访问
 * @param pageSize 		页面大小
 * @return				是否成功映射		
 */
	void mapPage(uint64_t vpn,uint64_t ppn,uint64_t userAccessable,uint64_t pageSize=__PAGE_SIZE);

	void fillPageFrame(uint64_t vpn,uint64_t userAccessable,uint64_t pageSize=__PAGE_SIZE);

/**
 * @brief 将虚拟页面的映射取消
 *
 * @param vpn 			虚拟页面号
 * @return				是否成功取消映射		
 */
	void unmapPage(uint64_t vpn);

	uint64_t getPML4PPN()const
	{
		return m_pml4PPN;
	}

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
 * @param vpn		虚拟页面的页面号
 * @return 			VMemMap结构，包含虚拟地址所在的页面结构表项地址、页面号、索引以及页面大小
 */
	static VMemMap resolveMap(uint64_t pml4PPN,uint64_t vpn);

/**
 * @brief 该函数用于解析虚拟页面号在类实例中的PML4下的映射信息，暂时只支持计算4KB页面
 *
 * @param vpn		虚拟页面的页面号
 * @return 			VMemMap结构，包含虚拟地址所在的页面结构表项地址、页面号、索引以及页面大小
 */
	VMemMap resolveMap(uint64_t vpn)
	{
		return resolveMap(m_pml4PPN,vpn);
	}

	static void mapKernelPage(uint64_t vpn,uint64_t ppn);

	static void unmapKernelPage(uint64_t vpn);

private:

	static void refreshPaging()
	{
		__asm__ __volatile__("movq %%cr3, %%rax; movq %%rax, %%cr3;" ::: "%rax");
	}

	template<class T>
	static void setPagingEntry(T* entries,size_t index,size_t ppn,
			uint64_t isToClear,uint64_t userAccessable,uint64_t writable);

	template<class T,class traits=type_traits<T>>
	static bool isNullPagingEntry(T* entries);

/**
 * @brief 管理PML4的物理页面号，代表了整个虚拟内存
 */
	uint64_t m_pml4PPN;
	
};

KEVOS_NSE_3(x64,x86,arch);

#endif
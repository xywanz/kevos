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

#include <arch/x86/x64/kpaging.h>


namespace mm::vm
{

/**
 * @brief 一个虚拟内存页的映射信息
 */
struct __packed__ VMemMap
{
	page::PML4E*  pml4;
	page::PDPTE*  pdpt;
	page::PDTE*	pdt;
	page::PTE*	pt;

	std::size_t pml4PPN;
	std::size_t pdptPPN;
	std::size_t pdtPPN;
	std::size_t ptPPN;

	std::size_t pageSize;

	std::size_t pml4Index;
	std::size_t pdptIndex;
	std::size_t pdtIndex;
	std::size_t ptIndex;
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
	void mapPage(std::size_t vpn,std::size_t ppn,std::size_t userAccessable,std::size_t pageSize=page::pageSize);

	void mapKernelSpace();

	void fillPageFrame(std::size_t vpn,std::size_t userAccessable,std::size_t pageSize=page::pageSize);

/**
 * @brief 将虚拟页面的映射取消
 *
 * @param vpn 			虚拟页面号
 * @return				是否成功取消映射		
 */
	void unmapPage(std::size_t vpn);

	std::size_t getPML4PPN()const
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
	static std::size_t getAddressFromPPN(std::size_t ppn,std::size_t pageSize=page::pageSize)
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
	static VMemMap resolveMap(std::size_t pml4PPN,std::size_t vpn);

/**
 * @brief 该函数用于解析虚拟页面号在类实例中的PML4下的映射信息，暂时只支持计算4KB页面
 *
 * @param vpn		虚拟页面的页面号
 * @return 			VMemMap结构，包含虚拟地址所在的页面结构表项地址、页面号、索引以及页面大小
 */
	VMemMap resolveMap(std::size_t vpn)
	{
		return resolveMap(m_pml4PPN,vpn);
	}

	static void mapKernelPage(std::size_t vpn,std::size_t ppn);

	static void unmapKernelPage(std::size_t vpn);

	void loadPML4()
	{
		__asm__ __volatile__("mov %%rax,%%cr3" : : "a"(getAddressFromPPN(m_pml4PPN)));
	}

	static void loadKernelPML4()
	{
		__asm__ __volatile__("mov %%rax,%%cr3" : : "a"(page::kernel::pml4));
	}

private:

	static void refreshPaging()
	{
		__asm__ __volatile__("movq %%cr3, %%rax; movq %%rax, %%cr3;" ::: "%rax");
	}

	static void bzero(std::size_t ppn);

	template<class T>
	static void setPagingEntry(T* entries,std::size_t index,std::size_t ppn,
			bool isToClear,std::size_t userAccessable,std::size_t writable);

	template<class T,class traits=page::type_traits<T>>
	static bool isNullPagingEntry(T* entries);

/**
 * @brief 管理PML4的物理页面号，代表了整个虚拟内存
 */
	std::size_t m_pml4PPN;
	
};

}

#endif
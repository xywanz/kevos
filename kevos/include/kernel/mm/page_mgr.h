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
*  @file     page_manager.h                            
*  @brief    对物理内存页面进行分配与回收等管理                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_KERNEL_MM_PAGEMGR_H_
#define _KEVOS_KERNEL_MM_PAGEMGR_H_

#include <sys/portable.h>
#include <arch/common/types.h>
#include <arch/common/paging.h>
#include <kernel/common/bitmap.h>
#include <kernel/mm/mem_layout.h>

KEVOS_NSS_2(kernel,mm);

template<class ByteType>
static constexpr size_t bitmapByteNeeded(size_t memorySize,size_t pageSize=__PAGE_SIZE)
{
	return memorySize/(pageSize*sizeof(ByteType));
}

class PageManager
{
public:

	static void initialize();

	static size_t allocate(size_t pageSize=__PAGE_SIZE);

	static void deallocate(size_t pPagePPN,size_t pageSize=__PAGE_SIZE);

private:
	static size_t m_size;
	static common::Bitmap<bitmapByteNeeded<unsigned int>(1024*1024*128),unsigned int> m_bitmap;
	static size_t m_cache;
};

KEVOS_NSE_2(mm,kernel);

#endif

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

#include <sys/types.h>
#include <kernel/mm/page_defs.h>
#include <kernel/utils/bitmap.h>
#include <kernel/mm/mem_layout.h>

namespace mm::page
{

template<class ByteType>
static constexpr std::size_t bitmapByteNeeded(std::size_t memorySize,std::size_t pageSize=pageSize)
{
	return memorySize/(pageSize*sizeof(ByteType));
}

class PageManager
{
public:

	static void initialize();

	static std::size_t allocate(std::size_t pageSize=pageSize);

	static void deallocate(std::size_t pPagePPN,std::size_t pageSize=pageSize);

private:
	static std::size_t m_size;
	static utils::Bitmap<bitmapByteNeeded<unsigned int>(1024*1024*128),unsigned int> m_bitmap;
	static std::size_t m_cache;
};

} 

#endif

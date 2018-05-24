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

KEVOS_NSS_3(kevos,kernel,mm);


class PageManager
{
public:

	PageManager();

	size_t allocate(size_t pageSize=__PAGE_SIZE);

	void deallocate(size_t pPagePPN,size_t pageSize=__PAGE_SIZE);

private:
	// common::Bitmap<DynamicBitmap,unsigned int> m_bitmap;
};


KEVOS_NSE_3(mm,kernel,kevos);

#endif

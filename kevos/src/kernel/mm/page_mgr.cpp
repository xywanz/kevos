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

#include <kernel/mm/page_mgr.h>

KEVOS_NSS_2(kernel,mm);

size_t PageManager::m_size=0;
common::Bitmap<bitmapByteNeeded<unsigned int>(1024*1024*128),unsigned int> PageManager::m_bitmap;
size_t PageManager::m_cache=0;

void PageManager::initialize()
{
	m_size=m_bitmap.size();
	size_t i;
	for(i=0;i<kernel_end_ppn;++i)
	{
		m_bitmap.set(i);
	}
	m_cache=i;
}

size_t PageManager::allocate(size_t pageSize)
{
	for(;m_cache<m_size;++m_cache)
	{
		if(__likely__(!m_bitmap.get(m_cache)))
		{
			m_bitmap.set(m_cache);
			return m_cache++;
		}
	}
	while(1)
	{
		for(m_cache=0;m_cache<m_size;++m_cache)
		{
			if(!m_bitmap.get(m_cache))
			{
				m_bitmap.set(m_cache);
				return m_cache++;
			}
		}
	}
}

void PageManager::deallocate(size_t pPagePPN,size_t pageSize)
{
	m_bitmap.unset(pPagePPN);
}

KEVOS_NSE_2(mm,kernel);

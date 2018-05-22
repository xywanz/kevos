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

#include <kernel/mm/kmem_mgr.h>

KEVOS_NSS_3(kevos,kernel,mm);


KernMemManager::KernMemManager(size_t vStartPagePPN,size_t vEndPagePPN)
	:m_memStart(reinterpret_cast<MemHeader*>(vStartPagePPN*__PAGE_SIZE))
{
	m_memEnd=reinterpret_cast<MemHeader*>(vEndPagePPN*__PAGE_SIZE-sizeof(MemHeader));
	m_memEnd->next=0;
	m_memEnd->size=sizeof(MemHeader);
	m_memEnd->used=1;
	m_memStart->next=m_memEnd;
	m_memStart->size=reinterpret_cast<char*>(m_memEnd)-reinterpret_cast<char*>(m_memStart);
	m_memStart->used=0;	
}

void* KernMemManager::allocate(size_t size)
{
	for(MemHeader* block=m_memStart;block!=m_memEnd;block=block->next)
	{
		
	}
}

void KernMemManager::deallocate(void* ptr)
{

}


KEVOS_NSE_3(mm,kernel,kevos);
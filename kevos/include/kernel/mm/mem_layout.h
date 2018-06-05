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
*  @file     mem_layout.h                            
*  @brief    段内存分布                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_KERNEL_MM_MEMLAYOUT_H_
#define _KEVOS_KERNEL_MM_MEMLAYOUT_H_


extern unsigned int text_start_address;
extern unsigned int text_end_address;

extern unsigned int data_start_address;
extern unsigned int data_end_address;

extern unsigned int bss_start_address;
extern unsigned int bss_end_address;

extern unsigned int kernel_start_address;
extern unsigned int kernel_end_address;

extern unsigned int kheap_start_address;
extern unsigned int kheap_end_address;

extern unsigned int kstack_start_address;
extern unsigned int kstack_end_address;


#define text_start_ppn		(reinterpret_cast<std::size_t>(&text_start_address)/__PAGE_SIZE)
#define text_end_ppn		(reinterpret_cast<std::size_t>(&text_end_address)/__PAGE_SIZE)

#define data_start_ppn		(reinterpret_cast<std::size_t>(&data_start_address)/__PAGE_SIZE)
#define data_end_ppn		(reinterpret_cast<std::size_t>(&data_end_address)/__PAGE_SIZE)

#define bss_start_ppn		(reinterpret_cast<std::size_t>(&bss_start_address)/__PAGE_SIZE)
#define bss_end_ppn			(reinterpret_cast<std::size_t>(&bss_end_address)/__PAGE_SIZE)

#define kstack_start_ppn	(reinterpret_cast<std::size_t>(&kstack_start_address)/__PAGE_SIZE)
#define kstack_end_ppn		(reinterpret_cast<std::size_t>(&kstack_end_address)/__PAGE_SIZE)

#define kheap_start_ppn		(reinterpret_cast<std::size_t>(&kheap_start_address)/__PAGE_SIZE)
#define kheap_end_ppn		(reinterpret_cast<std::size_t>(&kheap_end_address)/__PAGE_SIZE)

#define kernel_start_ppn	(reinterpret_cast<std::size_t>(&kernel_start_address)/__PAGE_SIZE)
#define kernel_end_ppn		(reinterpret_cast<std::size_t>(&kernel_end_address)/__PAGE_SIZE)


#endif

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

#ifndef _KEVOS_ARCH_X64_MEMLAYOUT_H_
#define _KEVOS_ARCH_X64_MEMLAYOUT_H_

#include <sys/portable.h>
#include <arch/x64/types.h>

KEVOS_NSS_3(kevos,arch,x64);


extern "C" uint64_t text_start_address;
extern "C" uint64_t text_end_address;

extern "C" uint64_t data_start_address;
extern "C" uint64_t data_end_address;

extern "C" uint64_t bss_start_address;
extern "C" uint64_t bss_end_address;

extern "C" uint64_t kernel_start_address;
extern "C" uint64_t kernel_end_address;


KEVOS_NSE_3(x64,arch,kevos);

#endif

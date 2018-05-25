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
*  @file     i8259.h                            
*  @brief                  
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/25
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_64_COMMON_I8259A_H_
#define _KEVOS_ARCH_x86_64_COMMON_I8259A_H_

#include <sys/portable.h>
#include <arch/common/types.h>

KEVOS_NSS_4(kevos,arch,x86_64,common);


class I8259A
{
public:

	static void initialize();

	static void enableIRQ(uint16_t num);

	static void disableIRQ(uint16_t num);
	
};


KEVOS_NSE_4(common,x86_64,arch,kevos);

#endif
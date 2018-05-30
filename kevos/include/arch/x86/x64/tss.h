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
*  @file     gdt.h                            
*  @brief    全局描述符表                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_X64_TSS_H_
#define _KEVOS_ARCH_x86_X64_TSS_H_

#include <arch/x86/x64/descriptor.h>

KEVOS_NSS_3(arch,x86,x64);

class TSS
{
public:

    static void initialize();

    static TaskStructureSegment tss;
};

KEVOS_NSE_3(x64,x86,arch);

#endif
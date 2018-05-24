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
*  @file     portable.h                            
*  @brief    统一不同编译器的功能，便于移植                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_SYS_PORTABLE_H_
#define _KEVOS_SYS_PORTABLE_H_


#ifdef __GNUC__

	/*结构内部紧密排列，不进行对齐操作。内核中很多数据结构都需要紧密的内存分布*/
	#define __packed__			__attribute__((packed))
	/*对齐，类定义对齐，或是实例地址对齐*/
	#define __aligned__(x)		__attribute__((aligned(x)))

	/*强制进行整数类型扩展，其他编译器也需要支持此特性*/
	#define __mode__(x)			__attribute__((__mode__(x)))
	
	/*设置段*/
	#define __section__(x)		__attribute__((section(x)))

	/*GCC内嵌ATT汇编*/
	#define __asm__(x)			asm(x)
	#define __asmv__(x)			__asm__ __volatile__(x)

	/*用于编译器优化分支选择*/
	#define __likely__(x)		__builtin_expect((x),1)
	#define __unlikely__(x)		__builtin_expect((x),0)

	#define __noreturn__		__attribute__((noreturn))

	#define __unreachable__()	__builtin_unreachable();		

#else

	#define __mode__(x)

#endif


/*
	以下定义是为了简化对命名空间的操作，实际上可能不是很好看TvT。Just for fun！

	这些定义可以组合使用，总之START和END所包含的命名空间数量要相等就行了
*/
#define KEVOS_NSS(x);	namespace x {
#define KEVOS_NSE(x);	}
#define KEVOS_NSS_2(x1,x2); namespace x1 { namespace x2{
#define KEVOS_NSE_2(x2,x1); }}
#define KEVOS_NSS_3(x1,x2,x3); namespace x1 { namespace x2 { namespace x3 {
#define KEVOS_NSE_3(x3,x2,x1); }}}
#define KEVOS_NSS_4(x1,x2,x3,x4); namespace x1 { namespace x2 { namespace x3 { namespace x4 {
#define KEVOS_NSE_4(x4,x3,x2,x1); }}}}
#define KEVOS_NSS_5(x1,x2,x3,x4,x5); namespace x1 { namespace x2 { namespace x3 { namespace x4 { namespace x5 {
#define KEVOS_NSE_5(x5,x4,x3,x2,x1); }}}}}
#define KEVOS_NSS_6(x1,x2,x3,x4,x5,x6); namespace x1 { namespace x2 { namespace x3 { \
				namespace x4 { namespace x5 { namespace x6 {
#define KEVOS_NSE_6(x6,x5,x4,x3,x2,x1); }}}}}}

#endif
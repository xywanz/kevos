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

/*******************************************************************************
*  @file     types.h    
*  @brief 统一不同架构下数值类型的表达
*  对所有类型进行了规范，每种架构下的编译器都必须提供以下类型以及它们在kevos中的名称：
*	  8位有符号整形		int8_t
*	  8位无符号整形		uint8_t
*	  16位有符号整形		int16_t
*	  16位无符号整形		uint16_t
*     32位有符号整形		int32_t
*     32位无符号整形		uint32_t
*     64位有符号整形		int64_t
*     64位无符号整形		uint64_t
*     32位浮点数			float32_t
*     64位双精度浮点数	float64_t
*     无符号尺度类型		size_t
*     有符号尺度类型		ssize_t
*     指针差类型			ptrdiff_t

*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
******************************************************************************/

#ifndef _KEVOS_ARCH_COMMON_TYPES_H_
#define _KEVOS_ARCH_COMMON_TYPES_H_

#include <sys/portable.h>
#include <arch/common/config.h>

#ifdef __KEVOS_X64__
	#include <arch/x86_64/x64/types.h>
#else

#include <sys/portable.h>

#ifndef _INT8_T
#define _INT8_T
using int8_t __mode__(__QI__)	=	char;
#endif

#ifndef _UINT8_T
#define _UINT8_T
using uint8_t __mode__(__QI__)	=	unsigned char;
#endif

#ifndef _INT16_T
#define _INT16_T
using int16_t __mode__(__HI__)	=	short;
#endif

#ifndef _UINT16_T
#define _UINT16_T
using uint16_t __mode__(__HI__)	=	unsigned short;
#endif

#ifndef _INT32_T
#define _INT32_T
using int32_t __mode__(__SI__)	=	int;
#endif

#ifndef _UINT32_T
#define _UINT32_T
using uint32_t	__mode__(__SI__) =	unsigned int;
#endif

#ifndef _INT64_T
#define _INT64_T
using int64_t __mode__(__DI__)	=	long;
#endif

#ifndef _UINT64_T
#define _UINT64_T
using uint64_t __mode__(__DI__)  =	unsigned long;
#endif

#ifndef _FLOAT32_T
#define _FLOAT32_T
using float32_t	=	float;
#endif

#ifndef _FLOAT64_T
#define _FLOAT64_T
using float64_t	=	double;
#endif

#ifndef _SIZE_T
#define _SIZE_T
using size_t    =	unsigned long;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
using ssize_t  	=	long;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
using ptrdiff_t	=	long;
#endif

#ifndef _POINTER_T
#define _POINTER_T
using pointer_t = 	unsigned long;
#endif

#endif


#endif
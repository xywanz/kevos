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
*  @file     types.h                            
*  @brief    x64架构下的数值类型                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_64_X64_TYPES_H_
#define _KEVOS_ARCH_x86_64_X64_TYPES_H_

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
using size_t    =	uint64_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
using ssize_t  	=	int64_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
using ptrdiff_t	=	int64_t;
#endif

#ifndef _POINTER_T
#define _POINTER_T
using pointer_t = 	uint64_t;
#endif

#endif
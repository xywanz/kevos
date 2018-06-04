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
*  @file     port.h                            
*  @brief    端口操作                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/25
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_COMMON_PORT_H_
#define _KEVOS_ARCH_x86_COMMON_PORT_H_

#include <arch/common/types.h>

namespace arch::x86::common
{

static inline uint8_t inportb(uint16_t port)
{
	uint8_t retVal;
	__asm__ __volatile__(
		"inb %1,%0"
		: "=a"(retVal)
		: "d"(port)
	);
	return retVal;
}

static inline uint16_t inportw(uint16_t port)
{
	uint16_t retVal;
	__asm__ __volatile__(
		"inw %1,%0"
		: "=a"(retVal)
		: "d"(port)
	);
	return retVal;
}

static inline uint32_t inportl(uint16_t port)
{
	uint32_t retVal;
	__asm__ __volatile__(
		"inl %1,%0"
		: "=a"(retVal)
		: "d"(port)
	);
	return retVal;
}

static inline void outportb(uint16_t port,uint8_t value)
{
	__asm__ __volatile__("outb %0,%1": : "a"(value), "d"(port));
}

static inline void outportw(uint16_t port,uint16_t value)
{
	__asm__ __volatile__("outw %0,%1": : "a"(value), "d"(port));
}

static inline void outportl(uint16_t port,uint32_t value)
{
	__asm__ __volatile__("outl %0,%1": : "a"(value), "d"(port));
}


static inline uint8_t inportbd(uint16_t port)
{
	uint8_t retVal;
	__asm__ __volatile__(
		"inb %1,%0"
		: "=a"(retVal)
		: "d"(port)
	);
	__asm__ __volatile__("nop\nnop");
	return retVal;
}

static inline uint16_t inportwd(uint16_t port)
{
	uint16_t retVal;
	__asm__ __volatile__(
		"inw %1,%0"
		: "=a"(retVal)
		: "d"(port)
	);
	__asm__ __volatile__("nop\nnop");
	return retVal;
}

static inline uint32_t inportld(uint16_t port)
{
	uint32_t retVal;
	__asm__ __volatile__(
		"inl %1,%0"
		: "=a"(retVal)
		: "d"(port)
	);
	__asm__ __volatile__("nop\nnop");
	return retVal;
}

static inline void outportbd(uint16_t port,uint8_t value)
{
	__asm__ __volatile__("outb %0,%1": : "a"(value), "d"(port));
	__asm__ __volatile__("nop\nnop");
}

static inline void outportwd(uint16_t port,uint16_t value)
{
	__asm__ __volatile__("outw %0,%1": : "a"(value), "d"(port));
	__asm__ __volatile__("nop\nnop");
}

static inline void outportld(uint16_t port,uint32_t value)
{
	__asm__ __volatile__("outl %0,%1": : "a"(value), "d"(port));
	__asm__ __volatile__("nop\nnop");
}

}	// end of namespace arch::x86::common

#endif

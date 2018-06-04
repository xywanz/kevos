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

#ifndef _KEVOS_ARCH_x86_COMMON_I8259A_H_
#define _KEVOS_ARCH_x86_COMMON_I8259A_H_

#include <arch/common/types.h>
#include <arch/x86/common/port.h>

namespace arch::x86::common
{

#define I8259A_PIC1_CONTROL_PORT	0x20
#define I8259A_PIC2_CONTROL_PORT	0xA0
#define I8259A_PIC1_DATA_PORT		0x21
#define I8259A_PIC2_DATA_PORT		0xA1

class I8259A
{
public:

	static void initialize();

	static void enableIRQ(uint16_t num)
	{
		mask &= (~(1<<num));
		if(num&8)
			outportb(I8259A_PIC2_DATA_PORT,mask>>8);
		else
			outportb(I8259A_PIC1_DATA_PORT,mask&0xFF);
	}

	static void enableAllIRQs()
	{
		mask = 0;
		outportb(I8259A_PIC1_DATA_PORT,0);
		outportb(I8259A_PIC2_DATA_PORT,0);
	}

	static void disableIRQ(uint16_t num)
	{
		mask |= (1<<num);
		if(num&8)
			outportb(I8259A_PIC2_DATA_PORT,mask>>8);
		else
			outportb(I8259A_PIC1_DATA_PORT,mask&0xFF);	
	}

	static void disableAllIRQs()
	{
		mask = 0xFFFF;
		outportb(I8259A_PIC1_DATA_PORT,0xFF);
		outportb(I8259A_PIC2_DATA_PORT,0xFF);
	}

	static void sendEOI(uint16_t num)
	{
		uint16_t port=num>7?I8259A_PIC2_CONTROL_PORT:I8259A_PIC1_CONTROL_PORT;
		outportb(port,0x20);
	}

private:
	static uint32_t mask;

};

}	// end of namespace arch::x86::common

#endif
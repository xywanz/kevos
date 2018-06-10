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
*  @file     multiboot.h                            
*  @brief    多重引导规范                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_x86_COMMON_MULTIBOOT_H_
#define _KEVOS_ARCH_x86_COMMON_MULTIBOOT_H_

#include <arch/common/types.h>

#define MULTIBOOT_PAGE_ALIGNED    (1U<<0)
#define MULTIBOOT_MEMORY_INFO     (1U<<1)
#define MULTIBOOT_VESA_INFO       (1U<<2)
#define MULTIBOOT_MAGIC           (0x1BADB002U)

namespace multiboot
{

struct __packed__ ElfSymbolTable
{
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
};

struct __packed__ Module
{
    uint32_t modStart;
  	uint32_t modEnd;
  	uint32_t string;
  	uint32_t reserved;
};

struct __packed__ MemoryMap
{
    uint32_t size;
    uint32_t baseAddrLow;
    uint32_t baseAddrHigh;
    uint32_t lengthLow;
    uint32_t lengthHigh;
    uint32_t type;
};

struct __packed__ VBEController
{
    uint8_t signature[4];
    uint16_t version;
    uint32_t oemString;
    uint32_t capabilities;
    uint32_t videoMode;
    uint16_t totalMemory;
    uint16_t oemSoftwareRev;
    uint32_t oemVendorName;
    uint32_t oemProductName;
    uint32_t oemProductRev;
    uint8_t reserved[222];
    uint8_t oemData[256];
};

struct __packed__ vbe_mode
{
    uint16_t modeAttributes;
    uint8_t winAAttributes;
    uint8_t winBAttributes;
    uint16_t winGranularity;
    uint16_t winSize;
    uint16_t winASegment;
    uint16_t winBSegment;
    uint32_t winFunc;
    uint16_t bytesPerScanline;
    
    // >=1.2
    uint16_t xResolution;
    uint16_t yResolution;
    uint8_t xCharSize;
    uint8_t yCharSize;
    uint8_t numberOfPlanes;
    uint8_t bitsPerPixel;
    uint8_t numberOfBanks;
    uint8_t memoryModel;
    uint8_t bankSize;
    uint8_t numberOfImagePages;
    uint8_t reserved0;
    
    // direct color
    uint8_t redMaskSize;
    uint8_t redFieldPosition;
    uint8_t greenMaskSize;
    uint8_t greenFieldPosition;
    uint8_t blueMaskSize;
    uint8_t blueFieldPosition;
    uint8_t reservedMaskSize;
    uint8_t reservedFieldPosition;
    uint8_t directColorModeInfo;
    
    // >=2.0
    uint32_t physBase;
    uint32_t reserved1;
    uint16_t reversed2;
    
    // >=3.0
    uint16_t linearBytesPerScanline;
    uint8_t bankedNumberOfImagePages;
    uint8_t linearNumberOfImagePages;
    uint8_t linearRedMaskSize;
    uint8_t linearRedFieldPosition;
    uint8_t linearGreenMaskSize;
    uint8_t linearGreenFieldPosition;
    uint8_t linearBlueMaskSize;
    uint8_t linearBlueFieldPosition;
    uint8_t linearReservedMaskSize;
    uint8_t linearReservedFieldPosition;
    uint32_t maxPixelClock;
    
    uint8_t reserved3[189];
};


struct __packed__ MultibootInfo
{
	uint32_t flags;
	uint32_t memLower;
	uint32_t memUpper;
	uint32_t bootDevice;
	uint32_t cmdline;
	uint32_t modsCount;
	uint32_t modsAddr;
	uint32_t mmapLength;
	uint32_t mmapAddr;
	uint32_t driversLength;
	uint32_t driversAddr;
	uint32_t configTable;
	uint32_t bootLoaderName;
	uint32_t apmTable;
	uint32_t vbeControlInfo;
	uint32_t vbeModeInfo;
	uint32_t vbeMod;
	uint32_t vbeInterfaceSeg;
	uint32_t vbeInterfaceOff;
	uint32_t vbeInterfaceLen;
};

struct __packed__ MultibootHeaderBase
{
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
};

struct __packed__ MultibootHeader
{
    MultibootHeaderBase headerBase;
//   if flags[16]
    uint32_t headerAddr;
    uint32_t loadAddr;
    uint32_t loadEndAddr;
    uint32_t bssEndAddr;
    uint32_t entryAddr;
//   if flags[2]
    uint32_t modeType;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};


#ifdef __KEVOS_MULTIBOOT__

#define __MAGIC ((uint32_t)MULTIBOOT_MAGIC)
#define __FLAGS ((uint32_t)(MULTIBOOT_PAGE_ALIGNED|MULTIBOOT_MEMORY_INFO))
#define __CHECKSUM ((uint32_t)(-(__MAGIC+__FLAGS)))

__section__(".boot")
static constexpr struct __packed__ {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} multibootHeader = {
        __MAGIC,
        __FLAGS,
        __CHECKSUM
};

#undef __MAGIC
#undef __FLAGS
#undef __CHECKSUM

#endif

}

#endif

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

#ifndef _KEVOS_ARCH_X86_COMMON_CPUID_H_
#define _KEVOS_ARCH_X86_COMMON_CPUID_H_

#include <arch/common/types.h>

namespace arch::x86::common
{

class CPUID
{
public:
	CPUID()
	{
	}

	void cpuid(uint32_t typeInfo);

	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
};

class CPUInfo
{
public:

	static CPUInfo& instance()
	{
		if(!cpuInfo)
		{
			cpuInfo=new CPUInfo();
		}
		return *cpuInfo;
	}

	static void release()
	{
		if(cpuInfo)
			delete cpuInfo;
		cpuInfo=nullptr;
	}

	uint32_t maxTypeInfo()const
	{
		return m_maxTypeInfo;
	}

	const char* identification()const
	{
		return (const char*)m_identification;
	}

	uint32_t steppingID()const
	{
		return m_steppingID;
	}

	uint32_t model()const
	{
		return m_model;
	}

	uint32_t family()const
	{
		return m_family;
	}

	uint32_t processorType()const
	{
		return m_processorType;
	}

	uint32_t extendedModel()const
	{
		return m_extendedModel;
	}

	uint32_t extendedFamily()const
	{
		return m_extendedFamily;
	}

	uint32_t brandIndex()const
	{
		return m_brandIndex;
	}

	uint32_t logicalProcessorCount()const
	{
		return m_logicalProcessorCount;
	}

	uint32_t clfushLineSize()const
	{
		return m_clfushLineSize;
	}

	bool fpuOnChip()const
	{
		return m_fpuOnChip;
	}

	bool vitual8086ModeEnhancement()const
	{
		return m_vitual8086ModeEnhancement;
	}

	bool debuggingExtension()const
	{
		return m_debuggingExtension;
	}

	bool pageSizeExtension()const
	{
		return m_pageSizeExtension;
	}

	bool timeStampCounter()const
	{
		return m_timeStampCounter;
	}

	bool rdmsrAndWRMSRInstructions()const
	{
		return m_rdmsrAndWRMSRInstructions;
	}

	bool physicalAddressExtension()const
	{
		return m_physicalAddressExtension;
	}

	bool machineCheckException()const
	{
		return m_machineCheckException;
	}

	bool cmpxchg8bInstruction()const
	{
		return m_cmpxchg8bInstruction;
	}

	bool apicOnChip()const
	{
		return m_apicOnChip;
	}

	bool sysenterAndSYSEXITInstructions()const
	{
		return m_sysenterAndSYSEXITInstructions;
	}

	bool memoryTypeRangeRegisters()const
	{
		return m_memoryTypeRangeRegisters;
	}

	bool pteGlobalBit()const
	{
		return m_pteGlobalBit;
	}

	bool machineCehckAchitecture()const
	{
		return m_machineCehckAchitecture;
	}

	bool conditionMoveInstructions()const
	{
		return m_conditionMoveInstructions;
	}

	bool pageAttributeTable()const
	{
		return m_pageAttributeTable;
	}

	bool pageSizeExtension4GB()const
	{
		return m_pageSizeExtension4GB;
	}

	bool processorSerialNumber()const
	{
		return m_processorSerialNumber;
	}

	bool clflushInstruction()const
	{
		return m_clflushInstruction;
	}

	bool debugStore()const
	{
		return m_debugStore;
	}

	bool acpiProcessorPerformanceModulationRegisters()const
	{
		return m_acpiProcessorPerformanceModulationRegisters;
	}

	bool mmxTechnology()const
	{
		return m_mmxTechnology;
	}

	bool fxsaveAndFXRSTORInstructions()const
	{
		return m_fxsaveAndFXRSTORInstructions;
	}

	bool sse()const
	{
		return m_sse;
	}

	bool sse2()const
	{
		return m_sse2;
	}

	bool selfSnoop()const
	{
		return m_selfSnoop;
	}

	bool thermalMonitor()const
	{
		return m_thermalMonitor;
	}

private:
	CPUInfo();
	static CPUInfo* cpuInfo;

	uint32_t m_maxTypeInfo;
	char 	 m_identification[13];

	uint32_t m_steppingID;
	uint32_t m_model;
	uint32_t m_family;
	uint32_t m_processorType;
	uint32_t m_extendedModel;
	uint32_t m_extendedFamily;

	uint32_t m_brandIndex;
	uint32_t m_clfushLineSize;
	uint32_t m_logicalProcessorCount;
	uint32_t m_apicPhysicalID;

	uint32_t m_fpuOnChip					:	1;
	uint32_t m_vitual8086ModeEnhancement	:	1;
	uint32_t m_debuggingExtension			:	1;
	uint32_t m_pageSizeExtension 			:	1;
	uint32_t m_timeStampCounter				:	1;	
	uint32_t m_rdmsrAndWRMSRInstructions	:	1;
	uint32_t m_physicalAddressExtension		:	1;
	uint32_t m_machineCheckException		:	1;
	uint32_t m_cmpxchg8bInstruction			:	1;
	uint32_t m_apicOnChip					:	1;
	uint32_t m_sysenterAndSYSEXITInstructions :	1;
	uint32_t m_memoryTypeRangeRegisters		:	1;
	uint32_t m_pteGlobalBit					:	1;
	uint32_t m_machineCehckAchitecture		:	1;
	uint32_t m_conditionMoveInstructions	:	1;
	uint32_t m_pageAttributeTable			:	1;
	uint32_t m_pageSizeExtension4GB			:	1;
	uint32_t m_processorSerialNumber		:	1;
	uint32_t m_clflushInstruction			:	1;
	uint32_t m_debugStore					:	1;
	uint32_t m_acpiProcessorPerformanceModulationRegisters : 1;
	uint32_t m_mmxTechnology				:	1;
	uint32_t m_fxsaveAndFXRSTORInstructions	:	1;
	uint32_t m_sse 							:	1;
	uint32_t m_sse2							:	1;
	uint32_t m_selfSnoop					:	1;
	uint32_t m_thermalMonitor				:	1;
	uint32_t m_reserved						:	5;
};

}	// end of namespace arch::x86::common

#endif

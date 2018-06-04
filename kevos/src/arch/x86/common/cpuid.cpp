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

#include <arch/x86/common/cpuid.h>

namespace arch::x86::common
{

void CPUID::cpuid(uint32_t typeInfo)
{
	__asm__(
		"movl %4,%%eax\n"
		"cpuid\n"
		"movl %%eax,%0\n"
		"movl %%ebx,%1\n"
		"movl %%ecx,%2\n"
		"movl %%edx,%3\n"
		:"=r"(eax),"=r"(ebx),"=r"(ecx),"=r"(edx)
		:"m"(typeInfo)
	);
}

CPUInfo* CPUInfo::cpuInfo=nullptr;

CPUInfo::CPUInfo()
{
	CPUID id;

	id.cpuid(0);

	m_maxTypeInfo=id.eax;
	*reinterpret_cast<uint32_t*>(m_identification)=id.ebx;
	*reinterpret_cast<uint32_t*>(m_identification+4)=id.edx;
	*reinterpret_cast<uint32_t*>(m_identification+8)=id.ecx;
	m_identification[12]=0;

	id.cpuid(1);

	m_steppingID=id.eax&0xF;
	m_model=(id.eax>>4)&0xF;
	m_family=(id.eax>>8)&0xF;
	m_processorType=(id.eax>>12)&0x3;
	m_extendedModel=(id.eax>>16)&0xF;
	m_extendedFamily=(id.eax>>20)&0xFF;

	m_brandIndex=id.ebx&0xFF;
	m_clfushLineSize=(id.ebx>>8)&0xFF;
	m_logicalProcessorCount=(id.ebx>>16)&0xFF;
	m_apicPhysicalID=(id.ebx>>24)&0xFF;

	m_fpuOnChip=id.edx&1;
	m_vitual8086ModeEnhancement=(id.edx>>1)&1;
	m_debuggingExtension=(id.edx>>2)&1;
	m_pageSizeExtension=(id.edx>>3)&1;
	m_timeStampCounter=(id.edx>>4)&1;
	m_rdmsrAndWRMSRInstructions=(id.edx>>5)&1;
	m_physicalAddressExtension=(id.edx>>6)&1;
	m_machineCheckException=(id.edx>>7)&1;
	m_cmpxchg8bInstruction=(id.edx>>8)&1;
	m_apicOnChip=(id.edx>>9)&1;
	m_sysenterAndSYSEXITInstructions=(id.edx>>11)&1;
	m_memoryTypeRangeRegisters=(id.edx>>12)&1;
	m_pteGlobalBit=(id.edx>>13)&1;
	m_machineCehckAchitecture=(id.edx>>14)&1;
	m_conditionMoveInstructions=(id.edx>>15)&1;
	m_pageAttributeTable=(id.edx>>16)&1;
	m_pageSizeExtension4GB=(id.edx>>17)&1;
	m_processorSerialNumber=(id.edx>>18)&1;
	m_clflushInstruction=(id.edx>>19)&1;
	m_debugStore=(id.edx>>21)&1;
	m_acpiProcessorPerformanceModulationRegisters=(id.edx>>22)&1;
	m_mmxTechnology=(id.edx>>23)&1;
	m_fxsaveAndFXRSTORInstructions=(id.edx>>24)&1;
	m_sse=(id.edx>>25)&1;
	m_sse2=(id.edx>>26)&1;
	m_selfSnoop=(id.edx>>27)&1;
	m_thermalMonitor=(id.edx>>29)&1;

	// TLB及缓存信息，TODO
	id.cpuid(2);
}

}	// end of namespace arch::x86::common

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

#ifndef _KEVOS_ARCH_x86_64_X64_INTERRUPT_H_
#define _KEVOS_ARCH_x86_64_X64_INTERRUPT_H_

#include <arch/common/types.h>

KEVOS_NSS_4(kevos,arch,x86_64,x64);

extern "C"
{
	void irqAsmHandler0();
	void irqAsmHandler1();

	void irqCppHandler0();
	void irqCppHandler1();
}


KEVOS_NSE_4(x64,x86_64,arch,kevos);

#endif

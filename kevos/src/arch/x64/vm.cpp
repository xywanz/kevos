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

#include <arch/x64/vm.h>

KEVOS_NSS_3(kevos,arch,x64);


PML4E 	__knPML4[KERNEL_PML4_SIZE] 	__aligned__(0x1000);
PDPTE 	__knPDPT[KERNEL_PDPT_SIZE]	__aligned__(0x1000);
PDTE  	__knPDT[KERNEL_PDT_SIZE] 	__aligned__(0x1000);
PTE   	__knPT[KERNEL_PT_SIZE] 		__aligned__(0x1000);


KEVOS_NSE_3(x64,arch,kevos);

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

/**
 * this linker script tells ld how to link and which symbols to add to the
 * kernel.x binary
 */
 
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(entry32)

physic_start_address = 0x100000;
virtual_start_address = 0xFFFFFFFF80000000;
address_difference = 0xFFFFFFFF00000000;
SECTIONS
{
  . = virtual_start_address + physic_start_address;

  .text : AT(ADDR(.text) - virtual_start_address)
  {
    PROVIDE(kernel_start_address = ABSOLUTE(.));

    text_start_address = .;
    *(.boot)
    *(.text)
    *(.text.*)
    text_end_address = .;
    *(.gnu.linkonce.r.*)
    ro_data_start_address = .;
    *(.rodata*)
    ro_data_end_address = .;
  }

  .data ALIGN(4096) : AT(physic_start_address + (data_start_address - text_start_address))
  {
    data_start_address = .;
    *(.data)
    . = ALIGN(4096);
    *(.gdt_stuff)
    data_end_address = .;
  }

  .bss ALIGN(4096) : AT(physic_start_address + (bss_start_address - text_start_address))
  {
    bss_start_address = .;
    *(.bss)
    *(COMMON) /* common symbols, usually placed in .bss */
    . = ALIGN(4096);
    bss_end_address = .;

    PROVIDE(kernel_end_address = .);
  }

}

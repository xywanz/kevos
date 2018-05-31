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
 * kernel.bin binary
 */
 
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(entry32)

virtual = 0x0000FFFF00000000;
physical = 0x100000;


SECTIONS
{
  . = physical;

  .text :
  {
    PROVIDE(kernel_start_address = ABSOLUTE(.));

    text_start_address = .;
    *(.boot)
    *(.text)
    *(.text.*)
    . = ALIGN(4096);
    text_end_address = .;
    *(.gnu.linkonce.r.*)
    ro_data_start_address = .;
    *(.rodata*)
    ro_data_end_address = .;
  }

  .data ALIGN(4096) :
  {
    data_start_address = .;
    *(.data)
    . = ALIGN(4096);
    data_end_address = .;
  }

  .bss ALIGN(4096) :
  {
    bss_start_address = .;
    *(.bss)
    *(COMMON)
    . = ALIGN(4096);
    bss_end_address = .;
  }

  .reserve.kern ALIGN(4096) :
  {
    kheap_start_address = .;
    *(.heap.kern)
    . = kheap_start_address + 0x1000000;
    . = ALIGN(4096);
    kheap_end_address = .;

    kstack_start_address = .;
    *(.stack.kern)
    . = kstack_start_address + 0x1000000;
    . = ALIGN(4096);
    kstack_end_address = .;
    PROVIDE(kernel_end_address = .);
  }
}


/*SECTIONS
{
  . = physical + virtual;

  .text : AT(ADDR(.text) - virtual)
  {
    PROVIDE(kernel_start_address = ABSOLUTE(.));

    text_start_address = .;
    *(.boot)
    *(.text)
    *(.text.*)
    . = ALIGN(4096);
    text_end_address = .;
    *(.gnu.linkonce.r.*)
    ro_data_start_address = .;
    *(.rodata*)
    ro_data_end_address = .;
  }

  .data ALIGN(4096) : AT(physical + data_start_address - text_start_address)
  {
    data_start_address = .;
    *(.data)
    . = ALIGN(4096);
    data_end_address = .;
  }

  .bss ALIGN(4096) : AT(physical + bss_start_address - text_start_address)
  {
    bss_start_address = .;
    *(.bss)
    *(COMMON)
    . = ALIGN(4096);
    bss_end_address = .;
  }

  .reserve.kern ALIGN(4096) : AT(physical + kheap_start_address - text_start_address)
  {
    kheap_start_address = .;
    *(.heap.kern)
    . = kheap_start_address + 0x1000000;
    . = ALIGN(4096);
    kheap_end_address = .;

    kstack_start_address = .;
    *(.stack.kern)
    . = kstack_start_address + 0x1000000;
    . = ALIGN(4096);
    kstack_end_address = .;
    PROVIDE(kernel_end_address = .);
  }
}*/
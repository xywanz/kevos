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

#include <arch/x86/common/i8259a.h>

namespace intr
{

uint32_t I8259A::mask=0xFFFF;

void I8259A::initialize()
{
    disableAllIRQs();

    io::outportb(I8259A_PIC1_CONTROL_PORT, 0x11);
    io::outportb(I8259A_PIC1_DATA_PORT, 0x20);
    io::outportb(I8259A_PIC1_DATA_PORT, 0x04);
    io::outportb(I8259A_PIC1_DATA_PORT, 0x01);
  
    io::outportb(I8259A_PIC2_CONTROL_PORT, 0x11);
    io::outportb(I8259A_PIC2_DATA_PORT, 0x28);
    io::outportb(I8259A_PIC2_DATA_PORT, 0x02);
    io::outportb(I8259A_PIC2_DATA_PORT, 0x01);

    for(uint16_t i=0;i<16;++i)
        sendEOI(i);
}

}

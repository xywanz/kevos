
#include <arch/x86_64/common/i8259a.h>

KEVOS_NSS_4(kevos,arch,x86_64,common);

uint32_t I8259A::mask=0xFFFF;

void I8259A::initialize()
{
	outportb(I8259A_PIC1_DATA_PORT,0xFF);
    outportb(I8259A_PIC2_DATA_PORT,0xFF);

	outportb(I8259A_PIC1_CONTROL_PORT, 0x11);
    outportb(I8259A_PIC1_DATA_PORT, 0x20);
    outportb(I8259A_PIC1_DATA_PORT, 0x04);
    outportb(I8259A_PIC1_DATA_PORT, 0x01);
  
    outportb(I8259A_PIC2_CONTROL_PORT, 0x11);
    outportb(I8259A_PIC2_DATA_PORT, 0x28);
    outportb(I8259A_PIC2_DATA_PORT, 0x02);
    outportb(I8259A_PIC2_DATA_PORT, 0x01);

  	for(uint16_t i=0;i<16;++i)
  		sendEOI(i);
}

KEVOS_NSE_4(common,x86_64,arch,kevos);


#include <arch/x86_64/common/i8259a.h>
#include <arch/x86_64/common/port.h>

KEVOS_NSS_4(kevos,arch,x86_64,common);


void I8259A::initialize()
{

}

void I8259A::enableIRQ(uint16_t num)
{

}

void I8259A::disableIRQ(uint16_t num)
{

}


KEVOS_NSE_4(common,x86_64,arch,kevos);

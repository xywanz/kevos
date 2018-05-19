
#include <sys/portable.h>

KEVOS_NSS_4(kevos,arch,x64,boot);


extern "C" void entry64()
{
	asm("movl $0xB8000,%eax");
	asm("movb $75,(%rax)");
	asm("movb $75,1(%rax)");
	while(1){}
}


KEVOS_NSE_4(boot,x64,arch,kevos);
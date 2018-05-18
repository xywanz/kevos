

extern "C" void entry64()
{
	asm("movl $0xB8000,%eax");
	asm("movb $75,(%rax)");
	asm("movb $75,1(%rax)");
	while(1){}
}
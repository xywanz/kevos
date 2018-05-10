
/*32位保护模式的启动代码，设置好环境后跳转到64位长模式
*/

/*此段代码编译成32位代码，4字节对齐
*/
asm(".code32");
asm(".align 4");

/*系统暂时只支持x64架构
*/
#define KEVOS_X64

#include <sys/portable.h>
#include <arch/common/multiboot.h>

#define __MAGIC ((uint32_t)MULTIBOOT_MAGIC)
#define __FLAGS ((uint32_t)MULTIBOOT_PAGE_ALIGNED|MULTIBOOT_MEMORY_INFO)
#define __CHECKSUM ((uint32_t)(-(__MAGIC+__FLAGS)))

__section__(".boot")
static const struct MultibootHeader0
{
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} multibootHeader =
    {
        __MAGIC,
        __FLAGS,
        __CHECKSUM
    };

struct __packed__ SegDescriptor
{
	uint16_t   limitLow;
    uint16_t   baseLowLow;
	uint8_t    baseLowMid;
    uint8_t    attrLow;
    uint8_t    limitHigh    :   4;
    uint8_t    attrHigh     :   4;
    uint8_t    baseLowHigh;
    uint32_t   baseHigh;
    uint32_t   reserve;
};

static void setSegDescriptor(SegDescriptor *desc)
{

}

extern "C" void entry32()
{
    asm("movl $0xB8000,%eax");
    asm("movb $75,0(%eax)");
    asm("movb $75,1(%eax)");
	while(1){}
}

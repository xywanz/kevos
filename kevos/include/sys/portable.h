
#ifndef _KEVOS_SYS_PORTABLE_H_
#define _KEVOS_SYS_PORTABLE_H_


#ifdef __GNUC__

	#define __packed__			__attribute__((packed))
	#define __aligned__(x)		__attribute__((aligned(x)))
	
	#define __section__(x)		__attribute__((section(x)))

	// #define __asm__(x)		asm(x)
	#define __asmv__(x)			__asm__ __volatile__(x)

	#define __likely__(x)		__builtin_expect((x),1)
	#define __unlikely__(x)		__builtin_expect((x),0)

#endif


#endif
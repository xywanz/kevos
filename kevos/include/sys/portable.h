
#ifndef _KEVOS_SYS_PORTABLE_H_
#define _KEVOS_SYS_PORTABLE_H_


#ifdef __GNUC__

#define __packed__		__attribute__((packed))

#define __aligned__(x)	__attribute__((aligned(x)))

#define __section__(x)	__attribute__((section(x)))

#endif


#endif
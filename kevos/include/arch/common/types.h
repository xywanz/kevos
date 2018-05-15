/*统一不同架构下数值类型的表达

  对所有类型进行了规范，每种架构下的编译器都必须提供以下类型以及它们在kevos中的名称：
  	8位有符号整形			int8_t
  	8位无符号整形			uint8_t
  	16位有符号整形		int16_t
  	16位无符号整形		uint16_t
	32位有符号整形		int32_t
	32位无符号整形		uint32_t
	64位有符号整形		int64_t
	64位无符号整形		uint64_t
	32位浮点数			float32_t
	64位双精度浮点数		float64_t
	无符号尺度类型		size_t
	有符号尺度类型		ssize_t
	指针差类型			ptrdiff_t
*/

#ifndef _KEVOS_ARCH_COMMON_TYPES_H_
#define _KEVOS_ARCH_COMMON_TYPES_H_


#ifdef __KEVOS_X64__
	#include <arch/x64/types.h>
#endif



#endif

#ifndef _KEVOS_ARCH_COMMON_BITMAP_H_
#define _KEVOS_ARCH_COMMON_BITMAP_H_

#include <sys/portable.h>
#include <arch/common/types.h>

KEVOS_NSS(kevos,arch,common);


#define DynamicBitMap	0


template<size_t ByteCount,class ByteType=uint8_t>
class Bitmap
{
public:
	Bitmap():
		m_bitmap({0})
	{
	}
	bool set(size_t index);
	bool unset(size_t index);
	bool get(size_t index);
private:
	ByteType m_bitmap[ByteCount];
	size_t m_size;
};


template<class ByteType>
class Bitmap<DynamicBitMap,ByteType>
{
private:
	ByteType* m_bitmap;
	size_t m_size;
};


KEVOS_NSE(common,arch,kevos);

#endif
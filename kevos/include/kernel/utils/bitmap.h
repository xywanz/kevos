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

/*****************************************************************************
*  @file     bitmap.h                            
*  @brief    位图                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_KERNEL_UTILS_BITMAP_H_
#define _KEVOS_KERNEL_UTILS_BITMAP_H_

#include <sys/types.h>

#include <array>
#include <algorithm>



namespace kernel::utils
{

#define DynamicBitmap	0


template<std::size_t byteCount,class ByteType=unsigned char>
class Bitmap
{
public:
	Bitmap()
	{
		std::fill(m_bitmap.begin(),m_bitmap.end(),0);
	}

	bool set(std::size_t index)
	{
		ByteType mask=1<<bitIndexOf(index);
		bool retVal=m_bitmap[byteIndexOf(index)]&mask;
		m_bitmap[byteIndexOf(index)]|=mask;
		return retVal;
	}

	bool unset(std::size_t index)
	{
		ByteType mask=1<<bitIndexOf(index);
		bool retVal=m_bitmap[byteIndexOf(index)]&mask;
		m_bitmap[byteIndexOf(index)]&=(~mask);
		return retVal;
	}

	bool get(std::size_t index)const
	{
		return m_bitmap[byteIndexOf(index)]&(1<<bitIndexOf(index));
	}

	static std::size_t size()
	{
		return s_size;	
	}

private:
	static constexpr std::size_t s_bitsPerByte=sizeof(ByteType)*8;
	static constexpr std::size_t s_size=byteCount*s_bitsPerByte;
	std::array<ByteType,byteCount> m_bitmap;
	

	static constexpr std::size_t bitIndexOf(std::size_t bit)
	{
		return bit%s_bitsPerByte;
	}

	static constexpr std::size_t byteIndexOf(std::size_t bit)
	{
		return bit/s_bitsPerByte;
	}
};


template<class ByteType>
class Bitmap<DynamicBitmap,ByteType>
{
public:
	Bitmap(ByteType* bitmap,std::size_t size);

	bool set(std::size_t index);

	bool unset(std::size_t index);

	bool get(std::size_t index)const;

private:
	static constexpr std::size_t s_bitsPerByte=sizeof(ByteType)*8;
	ByteType* m_bitmap;
	std::size_t m_size;

	static std::size_t bitIndexOf(std::size_t bit)
	{
		return bit%s_bitsPerByte;
	}

	static std::size_t byteIndexOf(std::size_t bit)
	{
		return bit/s_bitsPerByte;
	}
};

template<class ByteType>
Bitmap<DynamicBitmap,ByteType>::Bitmap(ByteType* bitmap,std::size_t size)
	:m_bitmap(bitmap),m_size(size)
{
	std::fill(m_bitmap,m_bitmap+size,0);
}

template<class ByteType>
bool Bitmap<DynamicBitmap,ByteType>::set(std::size_t index)
{
	std::size_t bitOffset=bitIndexOf(index);
	std::size_t byteOffset=byteIndexOf(index);
	ByteType mask=1<<bitOffset;
	bool retVal=m_bitmap[byteOffset]&mask;
	m_bitmap[byteOffset]|=mask;
	return retVal;
}

template<class ByteType>
bool Bitmap<DynamicBitmap,ByteType>::unset(std::size_t index)
{
	std::size_t bitOffset=bitIndexOf(index);
	std::size_t byteOffset=byteIndexOf(index);
	ByteType mask=1<<bitOffset;
	bool retVal=m_bitmap[byteOffset]&mask;
	m_bitmap[byteOffset]&=(~mask);
	return retVal;
}

template<class ByteType>
bool Bitmap<DynamicBitmap,ByteType>::get(std::size_t index)const
{
	return m_bitmap[byteIndexOf(index)]&(1<<bitIndexOf(index));
}

}	// end of namespace kernel::utils

#endif

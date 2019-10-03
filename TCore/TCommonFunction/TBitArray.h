#pragma once

namespace TCore
{
	namespace TBitArray
	{
		const u8 ONE[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
		const u8 ZERO[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

#define SET_0(array, index) (array &= ZERO[(index & 0x07)])
#define SET_1(array, index) (array |= ONE[(index & 0x07)])

#define GET_BIT_ARRAY_START(array, index) (array + (index>>3))

#define SET_BIT_ARRAY_0(array, index) SET_0(*GET_BIT_ARRAY_START(array, index), index)
#define SET_BIT_ARRAY_1(array, index) SET_1(*GET_BIT_ARRAY_START(array, index), index)

#define GET_BIT_ARRAY(array, index) (*GET_BIT_ARRAY_START(array, index) & ONE[(index & 0x07)])
	}
}

using namespace TCore::TBitArray;

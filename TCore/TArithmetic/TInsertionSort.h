//插入排序  在序列基本有序的时候效率较高
#pragma once 

namespace TCore
{
	namespace TArithmetic
	{
		template<typename T>
		T_INLINE void TInsertionSort(T* a_array, n32 a_nBegin, n32 a_nEnd)
		{
			n32 nL = a_nBegin + 1;
			for (n32 i = nL; i <= a_nEnd; i++)
			{
				T curValue = a_array[i];
				n32 nIdx = i - 1;
				while (nIdx >= 0 && a_array[nIdx] > curValue)
				{
					a_array[nIdx + 1] = a_array[nIdx];
					nIdx--;
				}
				a_array[nIdx + 1] = curValue;
			}
		}
	}
}


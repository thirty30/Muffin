#pragma once 

namespace TCore
{
	namespace TArithmetic
	{
		template<typename T>
		T_INLINE void TSelectionSort(T* a_array, T& a_max, n32 a_nBegin, n32 a_nEnd)
		{
			if (a_nBegin >= a_nEnd)
			{
				return;
			}
			T key = a_max;
			n32 nIndex = 0;
			for (n32 i = a_nBegin; i <= a_nEnd; i++)
			{
				if (key > a_array[i])
				{
					key = a_array[i];
					nIndex = i;
				}
			}
			a_array[nIndex] = a_array[a_nBegin];
			a_array[a_nBegin] = key;

			TSelectionSort(a_array, a_max, (a_nBegin + 1), a_nEnd);
		}
	}
}


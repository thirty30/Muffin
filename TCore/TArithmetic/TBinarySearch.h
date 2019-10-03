#pragma once 

namespace TCore
{
	namespace TArithmetic
	{
		template<typename T>
		T_INLINE n32 TBinarySearch(const T a_dest, T* a_array, n32 a_nBegin, n32 a_nEnd)
		{	
			n32 nL = a_nBegin;
			n32 nR = a_nEnd;
			while (nR >= nL)
			{
				n32 nMid = (nL + nR) / 2;
				if (a_array[nMid] == a_dest)
				{
					return nMid;
				}
				if (a_array[nMid] > a_dest)
				{
					nR = nMid - 1;
				}
				if (a_array[nMid] < a_dest)
				{
					nL = nMid + 1;
				}
			}
			return -1;
		}

		//////////////////////////////////////////////////////////////////////////

		//µÝ¹éÐ´·¨
		//template<typename T>
		//n32 TBinarySearch(const T a_dest, T* a_array, n32 a_nBegin, n32 a_nEnd)
		//{
		//	n32 nMid = (a_nBegin + a_nEnd) / 2;
		//	if (a_array[nMid] == a_dest)
		//	{
		//		return nMid;
		//	}
		//	if (a_nBegin >= a_nEnd)
		//	{
		//		return -1;
		//	}
		//	if (a_array[nMid] > a_dest)
		//	{
		//		return TBinarySearch(a_dest, a_array, a_nBegin, (nMid - 1));
		//	}
		//	if (a_array[nMid] < a_dest)
		//	{
		//		return TBinarySearch(a_dest, a_array, (nMid + 1), a_nEnd);
		//	}
		//	return -1;
		//}
	}
}


#pragma once

namespace TCore
{
	namespace TArithmetic
	{
		//需要排序的T类型,需要重载=
		//T& operator = (T& a_value)
		template<typename T>
		class TCompare
		{
		public:
			TCompare(){}
			virtual ~TCompare(){}
			virtual tbool compare(const T& a_key, const T& a_value) const T_PURE;
		};

		//该算法obj.compare()返回值  由小到大key<value   由大到小key>value
		template<typename T>
		T_INLINE void TQuickSort(T* a_pBegin, T* a_pEnd, TCompare<T>& a_obj)
		{
			if (a_pBegin >= a_pEnd)
			{
				return;
			}

			T pKey = *a_pBegin;
			T* pL = a_pBegin;
			T* pR = a_pEnd;

			while(pR > pL)
			{
				while (a_obj.compare(pKey, *pR) == true && pR > pL)
				{
					pR--;
				}
				while (a_obj.compare(pKey, *pL) == false && pR > pL)
				{
					pL++;
				}
				if (pL < pR)
				{
					T pTemp = *pR;
					*pR = *pL;
					*pL = pTemp;
				}
			}

			*a_pBegin = *pL;
			*pL = pKey;

			TQuickSort(a_pBegin, (pL - 1), a_obj);
			TQuickSort((pL + 1), a_pEnd, a_obj);
		}

		//////////////////////////////////////////////////////////////////////////

		template<typename T>
		void TQuickSort(T* a_array, n32 a_nBegin, n32 a_nEnd)
		{
			if (a_nBegin >= a_nEnd)
			{
				return;
			}

			n32 nL = a_nBegin;
			n32 nR = a_nEnd;
			T key = a_array[a_nBegin];

			while (nL < nR)
			{
				while (a_array[nR] >= key && nR > nL) 
				{
					nR--;
				}
				while (a_array[nL] <= key && nR > nL)
				{
					nL++;
				}
				if (nL < nR)
				{
					T temp = a_array[nR];
					a_array[nR] = a_array[nL];
					a_array[nL] = temp;
				}
			}
			a_array[a_nBegin] = a_array[nL];
			a_array[nL] = key;

			TQuickSort(a_array, a_nBegin, (nL - 1));
			TQuickSort(a_array, (nL + 1), a_nEnd);
		}

		//////////////////////////////////////////////////////////////////////////

		//以下函数是另一种交换思路，也是正确的
		//该算法obj.compare()返回值  由小到大key<=value   由大到小key>=value
		//template<class T>
		//void TQuickSort(T* a_pBegin, T* a_pEnd, TCompare<T>& a_obj)
		//{
		//	if( a_pBegin >= a_pEnd )
		//	{
		//		return;
		//	}
		//	T key = *a_pBegin;
		//	T* pL = a_pBegin;
		//	T* pR   = a_pEnd;

		//	while(pL < pR)
		//	{
		//		if (pL < pR && a_obj.compare(key, *pR))
		//		{
		//			pR--;
		//		}
		//		*pL = *pR;
		//		if (pL < pR && !a_obj.compare(key, *pL))
		//		{
		//			pL++;
		//		}
		//		*pR = *pL;
		//	}
		//	*pL = key;

		//	TQuickSort(a_pBegin, (pL - 1), a_obj);
		//	TQuickSort((pL + 1), a_pEnd, a_obj);
		//}
	}
}


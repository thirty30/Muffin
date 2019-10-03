//Á´Ê½Õ»½á¹¹
#pragma once

namespace TCore
{
	namespace TDataStructure
	{
		template<typename T, n32 LEN>
		class CTStack
		{
		private:
			T m_array[LEN + 1];
			n32 m_nTop;
		public:
			CTStack()
				: m_nTop(0)
			{
				TMemzero(m_array, sizeof(m_array));
			}
			~CTStack(){}
			tbool push(const T& a_data)
			{
				if (m_nTop >= LEN)
				{
					return false;
				}
				m_nTop++;
				m_array[m_nTop] = a_data;
				return true;
			}
			T* pop()
			{
				T* res = NULL;
				if (m_nTop >= 1)
				{
					res = &m_array[m_nTop];
					m_nTop--;
				}
				return res;
			}
			n32 getCount()
			{
				return (m_nTop - 1);
			}
			n32 getSize()
			{
				return LEN;
			}
			tbool isEmpty()
			{
				return (m_nTop - 1) == 0;
			}
		};
	}
}


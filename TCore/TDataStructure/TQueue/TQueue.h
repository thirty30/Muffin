//循环队列结构
#pragma once

namespace TCore
{
	namespace TDataStructure
	{
		template<typename T, n32 LEN>
		class CTQueue
		{
		private:
			T m_array[LEN];
			n32 m_nHead;
			n32 m_nTail;
			n32 m_nSize;
		public:
			CTQueue()
				: m_nHead(0)
				, m_nTail(0)
				, m_nSize(0)
			{
				TMemzero(m_array, sizeof(m_array));
			}
			~CTQueue(){}

			tbool push(const T& a_data)
			{
				if (m_nSize >= LEN)
				{
					return false;
				}
				m_array[m_nTail] = a_data;
				m_nTail++;
				m_nTail = m_nTail % LEN;
				m_nSize++;
				return true;
			}

			T* pop()
			{
				T* res = NULL;
				if (m_nSize > 0)
				{
					res = &m_array[m_nHead];
					m_nHead++;
					m_nHead = m_nHead % LEN;
					m_nSize--;
				}
				return res;
			}

			n32 getCount()
			{
				return m_nSize;
			}

			n32 getSize()
			{
				return LEN;
			}

			tbool isEmpty()
			{
				return (m_nSize == 0);
			}
		};
	}
}


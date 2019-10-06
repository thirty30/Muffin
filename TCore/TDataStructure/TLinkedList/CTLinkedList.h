#pragma once 

namespace TCore
{
	namespace TDataStructure
	{
		template<typename T>
		class T_DLL_EXPORT CTLinkedNode
		{
		public:
			T* m_pValue;
			CTLinkedNode<T>* m_pPrevious;
			CTLinkedNode<T>* m_pNext;

			CTLinkedNode()
			{
				this->m_pValue = NULL;
				this->m_pPrevious = NULL;
				this->m_pNext = NULL;
			}
		};

		template<typename T>
		class T_DLL_EXPORT CTLinkedList
		{
		private:
			CTLinkedNode<T>* m_pHead;
			CTLinkedNode<T>* m_pTail;
			n32 m_nCount;

		public:
			CTLinkedList()
			{
				this->m_pHead = NULL;
				this->m_pTail = NULL;
			}
			~CTLinkedList() {}

			CTLinkedNode<T>* AddNode(T* a_pValue)
			{
				CTLinkedNode<T>* pNewNode = new CTLinkedNode<T>();
				pNewNode->m_pValue = a_pValue;

				if (this->m_pHead == NULL)
				{
					this->m_pHead = pNewNode;
					this->m_pTail = pNewNode;
				}
				else
				{
					this->m_pTail->m_pNext = pNewNode;
					pNewNode->m_pPrevious = this->m_pTail;
					this->m_pTail = pNewNode;
				}
				this->m_nCount++;
				return pNewNode;
			}

			CTLinkedNode<T>* GetHeadNode()
			{
				return this->m_pHead;
			}

			CTLinkedNode<T>* GetTailNode()
			{
				return this->m_pTail;
			}

			void DeleteNode(CTLinkedNode<T>* a_pNode)
			{
				//sanshi mark todo
			}
		};

	}
}



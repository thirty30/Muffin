#pragma once 

namespace TCore
{
	namespace TDataStructure
	{
		template<typename T>
		class T_DLL_EXPORT TLinkedNode
		{
		public:
			T* m_pValue;
			TLinkedNode<T>* m_pPrevious;
			TLinkedNode<T>* m_pNext;

			TLinkedNode(T* a_pValue)
			{
				this->m_pValue = a_pValue;
				this->m_pPrevious = NULL;
				this->m_pNext = NULL;
			}
		};

		template<typename T>
		class T_DLL_EXPORT TLinkedList
		{
		private:
			TLinkedNode<T>* m_pHead;
			TLinkedNode<T>* m_pTail;
			n32 m_nCount;

		public:
			TLinkedList()
			{
				this->m_pHead = NULL;
				this->m_pTail = NULL;
				this->m_nCount = 0;
			}
			~TLinkedList() {}

			T_INLINE void PushBack(TLinkedNode<T>* a_pNewNode)
			{
				if (a_pNewNode == NULL)
				{
					return;
				}
				if (this->m_pHead == NULL)
				{
					this->m_pHead = a_pNewNode;
					this->m_pTail = a_pNewNode;
				}
				else
				{
					this->m_pTail->m_pNext = a_pNewNode;
					a_pNewNode->m_pPrevious = this->m_pTail;
					this->m_pTail = a_pNewNode;
				}
				this->m_nCount++;
			}

			T_INLINE void PushFront(TLinkedNode<T>* a_pNewNode)
			{
				if (a_pNewNode == NULL)
				{
					return;
				}
				if (this->m_pHead == NULL)
				{
					this->m_pHead = a_pNewNode;
					this->m_pTail = a_pNewNode;
				}
				else
				{
					this->m_pHead->m_pPrevious = a_pNewNode;
					a_pNewNode->m_pNext = this->m_pHead;
					this->m_pHead = a_pNewNode;
				}
				this->m_nCount++;
			}

			T_INLINE TLinkedNode<T>* GetHeadNode()
			{
				return this->m_pHead;
			}

			T_INLINE TLinkedNode<T>* GetTailNode()
			{
				return this->m_pTail;
			}

			T_INLINE n32 GetLength()
			{
				return this->m_nCount;
			}

			T_INLINE void RemoveNode(TLinkedNode<T>* a_pNode)
			{
				if (a_pNode == NULL)
				{
					return;
				}
				TLinkedNode<T>* pPrevious = a_pNode->m_pPrevious;
				TLinkedNode<T>* pNext = a_pNode->m_pNext;
				a_pNode->m_pPrevious = NULL;
				a_pNode->m_pNext = NULL;

				if (a_pNode == this->m_pHead)
				{
					if (pNext == NULL)
					{
						this->m_pHead = NULL;
						this->m_pTail = NULL;
					}
					else
					{
						pNext->m_pPrevious = NULL;
						this->m_pHead = pNext;
					}
				}
				else if (a_pNode == this->m_pTail)
				{
					if (pPrevious == NULL)
					{
						this->m_pHead = NULL;
						this->m_pTail = NULL;
					}
					else
					{
						pPrevious->m_pNext = NULL;
						this->m_pTail = pPrevious;
					}
				}
				else
				{
					pPrevious->m_pNext = pNext;
					pNext->m_pPrevious = pPrevious;
				}
				this->m_nCount--;
			}

			T_INLINE TLinkedNode<T>* PopFront()
			{
				TLinkedNode<T>* pNode = this->GetHeadNode();
				this->RemoveNode(pNode);
				return pNode;
			}

			T_INLINE TLinkedNode<T>* PopBack()
			{
				TLinkedNode<T>* pNode = this->GetTailNode();
				this->RemoveNode(pNode);
				return pNode;
			}
		};
	}
}



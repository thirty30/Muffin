//普通二叉树
#pragma once

namespace TCore
{
	namespace TDataStructure
	{
		class T_DLL_EXPORT CBTNode
		{
		private:
			CBTNode* m_pL;
			CBTNode* m_pR;
			n32 m_nNodeID;
		public:
			CBTNode()
				: m_pL(NULL)
				, m_pR(NULL)
				, m_nNodeID(0)
			{}
			virtual ~CBTNode(){}

			void setID(n32 a_nID) { m_nNodeID = a_nID; }
			n32 getID() { return m_nNodeID; }

			CBTNode* getLeftNode() { return m_pL; }
			tbool addLeftNode(CBTNode* a_pNode)
			{
				if (m_pL != NULL)
				{
					return false;
				}
				m_pL = a_pNode; 
				return true;
			}

			CBTNode* getRightNode() { return m_pR; }
			tbool addRightNode(CBTNode* a_pNode)
			{
				if (m_pR != NULL)
				{
					return false;
				}
				m_pR = a_pNode; 
				return true;
			}

			CBTNode* addNode(CBTNode* a_pNode)
			{
				if (m_pL == NULL)
				{
					m_pL = a_pNode;
					return m_pL;
				}
				if (m_pR == NULL)
				{
					m_pR = a_pNode;
					return m_pR;
				}
				return NULL;
			}
		};

		class T_DLL_EXPORT CBinaryTree
		{
		private:
			CBTNode* m_pRoot;	//根节点
			n32 m_nDep;			//二叉树深度
			n32 m_nNodeCount;	//元素个数

		private:
			CBTNode* findNode(CBTNode* a_pNode, n32 a_nID);
			void clearTree(CBTNode* a_pNode);
		public:
			CBinaryTree()
				: m_pRoot(NULL)
				, m_nDep(0)
				, m_nNodeCount(0)
			{}
			~CBinaryTree(){}

			tbool initBinaryTree(CBTNode* a_pNode);
			n32 addNode(CBTNode* a_pNode);		//如果插入成功返回正数
			CBTNode* findNode(n32 a_nID);
			void clear();
		};
	}
}


#include "stdafx.h"

tbool CBinaryTree::initBinaryTree( CBTNode* a_pNode )
{
	if (m_pRoot != NULL)
	{
		return false;
	}
	m_pRoot = a_pNode;
	m_pRoot->setID(++m_nNodeCount);
	m_nDep++;
	return true;
}

CBTNode* CBinaryTree::findNode( CBTNode* a_pNode, n32 a_nID )
{
	if (a_pNode == NULL)
	{
		return NULL;
	}
	if (a_pNode->getID() == a_nID)
	{
		return a_pNode;
	}
	CBTNode* pFind = NULL;
	pFind = findNode(a_pNode->getLeftNode(), a_nID);
	if (pFind != NULL)
	{
		return pFind;
	}
	else
	{
		pFind = findNode(a_pNode->getRightNode(), a_nID);
	}
	
	return pFind;
}

CBTNode* CBinaryTree::findNode( n32 a_nID )
{
	return findNode(m_pRoot, a_nID);
}

void CBinaryTree::clear()
{
	clearTree(m_pRoot);
}

void CBinaryTree::clearTree( CBTNode* a_pNode )
{
	if (a_pNode != NULL)
	{
		clearTree(a_pNode->getLeftNode());
		clearTree(a_pNode->getRightNode());
		delete a_pNode;
		a_pNode = NULL;
	}
}

n32 CBinaryTree::addNode( CBTNode* a_pNode )
{
	n32 nLimitCount = (n32)(1<<m_nDep) - 1;
	n32 nParentID = 0;
	if (nLimitCount == m_nNodeCount)
	{
		nParentID = (n32)(1<<(m_nDep - 1));
		CBTNode* pNode = findNode(m_pRoot, nParentID);
		if (pNode != NULL)
		{
			pNode->addLeftNode(a_pNode);
			pNode->getLeftNode()->setID(++m_nNodeCount);
			m_nDep++;
			return m_nNodeCount;
		}
		return 0;
	}

	nParentID = (m_nNodeCount + 1) / 2;
	CBTNode* pNode = findNode(m_pRoot, nParentID);
	if (pNode != NULL)
	{
		CBTNode* pNew = pNode->addNode(a_pNode);
		if (pNew != NULL)
		{
			pNew->setID(++m_nNodeCount);
			return m_nNodeCount;
		}
	}

	return 0;
}


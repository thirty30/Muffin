#include "CGameObject.h"
#include "GameObject/CGameObjectManager.h"
#include "Engine/Engine.h"

CGameObject::CGameObject()
{
	this->m_nMUFFINGUID = 0;
	this->m_bEnable = true;
	MUFFIN.GetGameObjectMgr()->AddObject(this);
}

CGameObject::~CGameObject()
{
	this->Clear();
	MUFFIN.GetGameObjectMgr()->RemoveObject(this);
}

void CGameObject::Init()
{
	TLinkedNode<CComponentBase*>* pNode = this->m_pComponents.GetHeadNode();
	while (pNode != NULL)
	{
		CComponentBase* pCom = pNode->m_pValue;
		if (pCom->m_bIsInit == false)
		{
			pCom->Init();
			pCom->m_bIsInit = true;
		}
		pNode = pNode->m_pNext;
	}
}

void CGameObject::Update()
{
	TLinkedNode<CComponentBase*>* pNode = this->m_pComponents.GetHeadNode();
	while (pNode != NULL)
	{
		tbool bIsEnable = pNode->m_pValue->m_bIsEnable;
		if (bIsEnable == true)
		{
			pNode->m_pValue->Update();
		}
		pNode = pNode->m_pNext;
	}
}

void CGameObject::Clear()
{
	while (this->m_pComponents.GetLength() > 0)
	{
		TLinkedNode<CComponentBase*>* pNode = this->m_pComponents.PopBack();
		pNode->m_pValue->Clear();
		delete pNode->m_pValue;
		delete pNode;
	}
}

#include "CGameObject.h"
#include "GameObject/CGameObjectManager.h"
#include "Engine/Engine.h"

CGameObject::CGameObject()
{
	this->m_nMUFFINGUID = 0;
	this->m_bEnable = true;
	this->m_bIsInited = false;
	MUFFIN.GetGameObjectMgr()->AddObject(this);
}

CGameObject::~CGameObject()
{
	this->Clear();
}

T_INLINE void CGameObject::SetEnable(tbool a_bEnable)
{
	this->m_bEnable = a_bEnable;
	TLinkedNode<CComponentBase*>* pNode = this->m_pComponents.GetHeadNode();
	while (pNode != NULL)
	{
		if (this->m_bEnable == false)
		{
			pNode->m_pValue->Disable();
		}
		else
		{
			pNode->m_pValue->Enable();
		}
		pNode = pNode->m_pNext;
	}
}

void CGameObject::Destory()
{
	MUFFIN.GetGameObjectMgr()->RemoveObject(this);
	delete this;
}

void CGameObject::CallBackCollision(const SCollisionInfo& a_rCollision)
{
	TLinkedNode<CComponentBase*>* pNode = this->m_pComponents.GetHeadNode();
	while (pNode != NULL)
	{
		tbool bIsEnable = pNode->m_pValue->m_bIsEnable;
		if (bIsEnable == true)
		{
			pNode->m_pValue->OnCollider(a_rCollision);
		}
		pNode = pNode->m_pNext;
	}
}

void CGameObject::Init()
{
	if (m_bIsInited == true)
	{
		return;
	}
	this->m_bIsInited = true;
	TLinkedNode<CComponentBase*>* pNode = this->m_pComponents.GetHeadNode();
	while (pNode != NULL)
	{
		pNode->m_pValue->Init();
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

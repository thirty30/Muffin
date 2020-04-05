#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "Component/CComponentBase.h"
#include "Transform/CTransform.h"

class CLineTween;
class T_DLL_EXPORT CGameObject
{
private:
	u64 m_nMUFFINGUID;
	tbool m_bEnable;
	CTransform m_pTransform;
	TLinkedList<CComponentBase*> m_pComponents;
	tbool m_bIsInited;

	friend class CGameObjectManager;

private:
	void Init();
	void Update();
	void Clear();

public:
	CGameObject();
	virtual ~CGameObject();

	T_INLINE u64 GetGameObjectID() { return this->m_nMUFFINGUID; }
	T_INLINE tbool IsEnable() { return this->m_bEnable; }
	T_INLINE void SetEnable(tbool a_bEnable);
	T_INLINE CTransform& GetTransform() { return this->m_pTransform; }
	T_INLINE void Destory();
	void CallBackCollision(const SCollisionInfo& a_rCollision);

	template<typename T>
	T* AddComponent();
	template<typename T>
	T* AddComponent(T* a_pCom);
	template<typename T>
	T* GetComponent();
};

template<typename T>
T* CGameObject::AddComponent()
{
	CComponentBase* pComponent = new T();
	pComponent->m_pGameObect = this;
	TLinkedNode<CComponentBase*>* pNode = new TLinkedNode<CComponentBase*>(pComponent);
	this->m_pComponents.PushBack(pNode);
	return static_cast<T*>(pComponent);
}

template<typename T>
T* CGameObject::AddComponent(T* a_pCom)
{
	CComponentBase* pComponent = static_cast<CComponentBase*>(a_pCom);
	pComponent->m_pGameObect = this;
	TLinkedNode<CComponentBase*>* pNode = new TLinkedNode<CComponentBase*>(pComponent);
	this->m_pComponents.PushBack(pNode);
	return a_pCom;
}

template<typename T>
T* CGameObject::GetComponent()
{
	TLinkedNode<CComponentBase*>* pHead = this->m_pComponents.GetHeadNode();
	while (pHead != NULL)
	{
		if (typeid(*pHead->m_pValue) == typeid(T))
		{
			return static_cast<T*>(pHead->m_pValue);
		}
		pHead = pHead->m_pNext;
	}
	return NULL;
}

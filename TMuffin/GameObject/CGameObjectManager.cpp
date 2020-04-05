#include "CGameObjectManager.h"
#include "CGameObject.h"
#include "Engine/Engine.h"
#include "Utility/CGUIDMaker.h"

CGameObjectManager::CGameObjectManager()
{
	this->m_mapID2Node.clear();
	this->m_vecUnsettled.clear();
}

CGameObjectManager::~CGameObjectManager()
{
	while (this->m_listGameObject.GetLength() > 0)
	{
		TLinkedNode<CGameObject*>* pNode = this->m_listGameObject.PopBack();
		delete pNode->m_pValue;
		delete pNode;
	}
	this->m_mapID2Node.clear();
	this->m_vecUnsettled.clear();
}

void CGameObjectManager::AddObject(CGameObject* a_pGameObject)
{
	a_pGameObject->m_nMUFFINGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_GAMEOBJECT);
	TLinkedNode<CGameObject*>* pNode = new TLinkedNode<CGameObject*>(a_pGameObject);
	this->m_listGameObject.PushBack(pNode);
	this->m_mapID2Node[a_pGameObject->m_nMUFFINGUID] = pNode;
	this->m_vecUnsettled.push_back(a_pGameObject);
}

CGameObject* CGameObjectManager::FindObject(u64 a_nGUID)
{
	hash_map<u64, TLinkedNode<CGameObject*>*>::iterator iter = this->m_mapID2Node.find(a_nGUID);
	if (iter == this->m_mapID2Node.end())
	{
		return NULL;
	}
	return iter->second->m_pValue;
}

TLinkedNode<CGameObject*>* CGameObjectManager::FindObjectNode(u64 a_nGUID)
{
	hash_map<u64, TLinkedNode<CGameObject*>*>::iterator iter = this->m_mapID2Node.find(a_nGUID);
	if (iter == this->m_mapID2Node.end())
	{
		return NULL;
	}
	return iter->second;
}

void CGameObjectManager::RemoveObject(CGameObject* a_pGameObject)
{
	u64 nGUID = a_pGameObject->m_nMUFFINGUID;
	TLinkedNode<CGameObject*>* pNode = this->FindObjectNode(nGUID);
	if (pNode == NULL)
	{
		return;
	}
	this->m_listGameObject.RemoveNode(pNode);
	delete pNode;
	this->m_mapID2Node.erase(nGUID);
}

void CGameObjectManager::Init()
{
	for (n32 i = 0; i < this->m_vecUnsettled.size(); i++)
	{
		this->m_vecUnsettled[i]->Init();
	}
	this->m_vecUnsettled.clear();
}

void CGameObjectManager::Update()
{
	TLinkedNode<CGameObject*>* pHead = this->m_listGameObject.GetHeadNode();
	while (pHead != NULL)
	{
		if (pHead->m_pValue->m_bIsInited == true)
		{
			pHead->m_pValue->Update();
		}
		pHead = pHead->m_pNext;
	}
}


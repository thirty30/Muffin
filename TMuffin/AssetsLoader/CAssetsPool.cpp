#include "CAssetsPool.h"
#include "CAssetsWorker.h"
#include "AssetObject/CAssetObject.h"
#include "Engine/Engine.h"

SLoadAssetsTask* CreateLoadAssetsTask()
{
	return MUFFIN.GetAssetsPoolMgr()->CreateTask();
}

extern T_DLL_EXPORT CAssetObject* FindExistedAsset(tstring a_strFileName)
{
	return MUFFIN.GetAssetsPoolMgr()->FindAsset(a_strFileName);
}

extern T_DLL_EXPORT void AddExistedAsset(tstring a_strFileName, CAssetObject* a_pAsset)
{
	MUFFIN.GetAssetsPoolMgr()->AddAsset(a_strFileName, a_pAsset);
}

CAssetsPool::CAssetsPool()
{
	this->m_vecWorker.clear();
	this->m_mapExistedAssets.clear();
}

CAssetsPool::~CAssetsPool()
{

}

void CAssetsPool::CreateWorker(n32 a_nNum)
{
	for (n32 i = 0; i < a_nNum; i++)
	{
		CAssetsWorker* pUnit = new CAssetsWorker();
		TThreadWorker* pWorker = new TThreadWorker(pUnit);
		pWorker->CreateThread();
		this->m_vecWorker.push_back(pWorker);
	}
}

SLoadAssetsTask* CAssetsPool::CreateTask()
{
	SLoadAssetsTask* pNewTask = new SLoadAssetsTask();
	TLinkedNode<SLoadAssetsTask*>* pNode = new TLinkedNode<SLoadAssetsTask*>(pNewTask);
	this->m_TaskUnSettledList.PushBack(pNode);
	return pNewTask;
}

void CAssetsPool::Update()
{
	// 1. copy unsettled tasks to waiting task list
	if (this->m_TaskUnSettledList.GetLength() > 0)
	{
		this->m_Lock2Waitting.Lock();
		this->m_TaskWaitingList.PushBack(&this->m_TaskUnSettledList);
		this->m_Lock2Waitting.UnLock();

		this->m_TaskUnSettledList.Clear();
	}

	// 2. copy finished tasks to settled task list
	this->m_Lock2Finished.Lock();
	if (this->m_TaskFinishedList.GetLength() > 0)
	{
		this->m_TaskSettledList.PushBack(&this->m_TaskFinishedList);
		this->m_TaskFinishedList.Clear();
	}
	this->m_Lock2Finished.UnLock();

	// 3. deal settled tasks, put the task on main thread, do some stuffs after multi-thread loading
	TLinkedNode<SLoadAssetsTask*>* pNode = this->m_TaskSettledList.GetHeadNode();
	while (pNode != NULL)
	{
		SLoadAssetsTask* pTask = pNode->m_pValue;
		if (pTask->m_pAssetObject->InitAfterLoad() == false)
		{
			delete pTask->m_pAssetObject;
			pTask->m_pAssetObject = NULL;
		}
		pNode = pNode->m_pNext;
	}
}

void CAssetsPool::UpdateCallBack()
{
	TLinkedNode<SLoadAssetsTask*>* pNode = this->m_TaskSettledList.PopFront();
	while (pNode != NULL)
	{
		SLoadAssetsTask* pTask = pNode->m_pValue;
		pTask->m_funcCallBack(pTask->m_pCustomData, pTask->m_pAssetObject);
		delete pTask;
		delete pNode;

		pNode = this->m_TaskSettledList.PopFront();
	}
}

TLinkedNode<SLoadAssetsTask*>* CAssetsPool::PickATask()
{
	if (this->m_TaskWaitingList.GetLength() <= 0)
	{
		return NULL;
	}
	this->m_Lock2Waitting.Lock();
	TLinkedNode<SLoadAssetsTask*>* pNode = this->m_TaskWaitingList.PopFront();
	this->m_Lock2Waitting.UnLock();
	if (pNode == NULL)
	{
		return NULL;
	}
	return pNode;
}

void CAssetsPool::PushFinishedTask(TLinkedNode<SLoadAssetsTask*>* a_pNode)
{
	this->m_Lock2Finished.Lock();
	this->m_TaskFinishedList.PushBack(a_pNode);
	this->m_Lock2Finished.UnLock();
}

void CAssetsPool::AddAsset(tstring a_strFileName, CAssetObject* a_pAsset)
{
	this->m_Lock2ExistedMap.Lock();

	hash_map<tstring, CAssetObject*>::const_iterator iter = this->m_mapExistedAssets.find(a_strFileName);
	if (iter == this->m_mapExistedAssets.end())
	{
		this->m_mapExistedAssets[a_strFileName] = a_pAsset;
	}
	
	this->m_Lock2ExistedMap.UnLock();
}

CAssetObject* CAssetsPool::FindAsset(tstring a_strFileName)
{
	CAssetObject* pAsset = NULL;

	this->m_Lock2ExistedMap.Lock();

	hash_map<tstring, CAssetObject*>::const_iterator iter = this->m_mapExistedAssets.find(a_strFileName);
	if (iter != this->m_mapExistedAssets.end())
	{
		pAsset = iter->second;
	}

	this->m_Lock2ExistedMap.UnLock();

	return pAsset;
}


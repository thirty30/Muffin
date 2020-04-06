#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "AssetsDefine.h"

extern T_DLL_EXPORT SLoadAssetsTask* CreateLoadAssetsTask();
extern T_DLL_EXPORT CAssetObject* FindExistedAsset(tstring a_strFileName);
extern T_DLL_EXPORT void AddExistedAsset(tstring a_strFileName, CAssetObject* a_pAsset);

class CAssetsPool
{
private:
	vector<TThreadWorker*> m_vecWorker;

	TLinkedList<SLoadAssetsTask*> m_TaskUnSettledList;
	TLinkedList<SLoadAssetsTask*> m_TaskWaitingList;	//shared with multi-thread

	TLinkedList<SLoadAssetsTask*> m_TaskFinishedList;	//shared with multi-thread
	TLinkedList<SLoadAssetsTask*> m_TaskSettledList;

	TThreadCriticalSection m_Lock2Waitting;
	TThreadCriticalSection m_Lock2Finished;

	hash_map<tstring, CAssetObject*> m_mapExistedAssets;
	TThreadCriticalSection m_Lock2ExistedMap;

public:
	CAssetsPool();
	~CAssetsPool();

	void CreateWorker(n32 a_nNum = 1);
	SLoadAssetsTask* CreateTask();
	void Update();
	void UpdateCallBack();

	TLinkedNode<SLoadAssetsTask*>* PickATask();
	void PushFinishedTask(TLinkedNode<SLoadAssetsTask*>* a_pNode);

	void AddAsset(tstring a_strFileName, CAssetObject* a_pAsset);
	CAssetObject* FindAsset(tstring a_strFileName);
};


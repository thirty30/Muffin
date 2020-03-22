#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "AssetsDefine.h"

extern T_DLL_EXPORT SLoadAssetsTask* CreateLoadAssetsTask();

class CAssetsPool : public CSingleton<CAssetsPool>
{
private:
	vector<TThreadWorker*> m_vecWorker;

	TLinkedList<SLoadAssetsTask*> m_TaskUnSettledList;
	TLinkedList<SLoadAssetsTask*> m_TaskWaitingList;	//shared with multi-thread

	TLinkedList<SLoadAssetsTask*> m_TaskFinishedList;	//shared with multi-thread
	TLinkedList<SLoadAssetsTask*> m_TaskSettledList;

	TThreadCriticalSection m_Lock2Waitting;
	TThreadCriticalSection m_Lock2Finished;


public:
	CAssetsPool();
	~CAssetsPool();

	void CreateWorker(n32 a_nNum = 1);
	SLoadAssetsTask* CreateTask();
	void Update();
	void UpdateCallBack();

	TLinkedNode<SLoadAssetsTask*>* PickATask();
	void PushFinishedTask(TLinkedNode<SLoadAssetsTask*>* a_pNode);
};


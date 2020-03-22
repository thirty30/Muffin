#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "AssetsDefine.h"

class CAssetsWorker : public TThreadInterface
{
private:
	EAssetsWorkerState m_eState;
	TLinkedNode<SLoadAssetsTask*>* m_pCurrentTaskNode;

public:
	CAssetsWorker();
	~CAssetsWorker();

	virtual void Run();
	tbool PickTask();
	void ProcessTask();
	void FinishTask();
};



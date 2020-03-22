#include "CAssetsWorker.h"
#include "CAssetsPool.h"
#include "AssetObject/CAssetObject.h"
#include "AssetObject/CMesh.h"
#include "AssetObject/CTexture.h"
#include "AssetObject/CMaterial.h"

CAssetsWorker::CAssetsWorker()
{
	this->m_eState = EAWS_INIT;
	this->m_pCurrentTaskNode = NULL;
}

CAssetsWorker::~CAssetsWorker()
{

}

void CAssetsWorker::Run()
{
	while (true)
	{
		switch (this->m_eState)
		{
		case EAWS_INIT:
		{
			this->m_eState = EAWS_WAIT_TASK;
		}
		break;
		case EAWS_WAIT_TASK:
		{
			TSleep(30);
			this->m_eState = EAWS_PICK_TASK;
		}
		break;
		case EAWS_PICK_TASK:
		{
			tbool bIsPicked = this->PickTask();
			if (bIsPicked == true)
			{
				this->m_eState = EAWS_PROCESS_TASK;
			}
			else
			{
				this->m_eState = EAWS_WAIT_TASK;
			}
		}
		break;
		case EAWS_PROCESS_TASK:
		{
			this->ProcessTask();
			this->m_eState = EAWS_FINISH_TASK;
		}
		break;
		case EAWS_FINISH_TASK:
		{
			this->FinishTask();
			this->m_eState = EAWS_PICK_TASK;
			TSleep(1);
		}
		break;
		default:
			break;
		}
	}
}

tbool CAssetsWorker::PickTask()
{
	this->m_pCurrentTaskNode = CAssetsPool::GetSingleton().PickATask();
	if (this->m_pCurrentTaskNode == NULL)
	{
		return false;
	}
	return true;
}

void CAssetsWorker::ProcessTask()
{
	SLoadAssetsTask* pTask = this->m_pCurrentTaskNode->m_pValue;
	if (pTask == NULL)
	{
		return;
	}

	CAssetObject* pAssetObject = NULL;
	switch (pTask->m_eTaskType)
	{
	case ELATT_LOAD_MESH:
	{
		pAssetObject = new CMesh();
	}
	break;
	case ELATT_LOAD_TEXTURE:
	{
		pAssetObject = new CTexture();
	}
	break;
	case ELATT_LOAD_MATERIAL:
	{
		pAssetObject = new CMaterial();
	}
	break;
	case ELATT_LOAD_ANIMATION:
	{

	}
	break;
	default:
		break;
	}

	if (pAssetObject == NULL)
	{
		return;
	}
	if (pAssetObject->LoadToMemory(pTask->m_strFilePath.c_str()) == false)
	{
		delete pAssetObject;
		return;
	}

	pTask->m_pAssetObject = pAssetObject;
}

void CAssetsWorker::FinishTask()
{
	CAssetsPool::GetSingleton().PushFinishedTask(this->m_pCurrentTaskNode);
	this->m_pCurrentTaskNode = NULL;
}


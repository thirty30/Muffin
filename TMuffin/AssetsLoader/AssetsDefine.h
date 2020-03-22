#pragma once
#include "TMuffinSysInclude.h"
#include "AssetObject/CAssetObject.h"

typedef void (*LoadAssetsCallBack)(void* a_pCustomData, CAssetObject* a_pObject);

enum EAssetsWorkerState
{
	EAWS_INIT = 0,
	EAWS_WAIT_TASK,
	EAWS_PICK_TASK,
	EAWS_PROCESS_TASK,
	EAWS_FINISH_TASK
};

enum ELoadAssetsTaskType
{
	ELATT_INIT = 0,
	ELATT_LOAD_MESH,
	ELATT_LOAD_TEXTURE,
	ELATT_LOAD_MATERIAL,
	ELATT_LOAD_ANIMATION,

	ELATT_LOAD_END,
};

struct SLoadAssetsTask
{
	ELoadAssetsTaskType m_eTaskType;
	tstring m_strFilePath;
	void* m_pCustomData;
	LoadAssetsCallBack m_funcCallBack;

	CAssetObject* m_pAssetObject;

	SLoadAssetsTask()
	{
		this->m_eTaskType = ELATT_INIT;
		this->m_pCustomData = NULL;
		this->m_funcCallBack = NULL;
		this->m_pAssetObject = NULL;
	}
};

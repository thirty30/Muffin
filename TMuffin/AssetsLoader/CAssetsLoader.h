#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "AssetObject/CAssetObject.h"
#include "AssetObject/CMesh.h"
#include "AssetsDefine.h"
#include "CAssetsPool.h"

class T_DLL_EXPORT CAssetsLoader
{
public:
	template <typename T>
	static T* Load(const tcchar* a_strFilePath, tbool a_bLoadNew = false);

	template <typename T>
	static void LoadASync(const tcchar* a_strFilePath, void* a_pCustomData, LoadAssetsCallBack a_funcCallback);
};

template <typename T>
T* CAssetsLoader::Load(const tcchar* a_strFilePath, tbool a_bLoadNew)
{
	//if (a_bLoadNew == false)
	//{
	//	CAssetObject* pAsset = FindExistedAsset(a_strFilePath);
	//	if (pAsset != NULL)
	//	{
	//		return static_cast<T*>(pAsset);
	//	}
	//}

	CAssetObject* pObj = new T();
	if (pObj->LoadToMemory(a_strFilePath) == false)
	{
		delete pObj;
		return NULL;
	}
	if (pObj->InitAfterLoad() == false)
	{
		delete pObj;
		return NULL;
	}
	AddExistedAsset(a_strFilePath, pObj);
	return static_cast<T*>(pObj);
}

template <typename T>
void CAssetsLoader::LoadASync(const tcchar* a_strFilePath, void* a_pCustomData, LoadAssetsCallBack a_funcCallback)
{
	SLoadAssetsTask* pTask = CreateLoadAssetsTask();
	pTask->m_funcCallBack = a_funcCallback;
	pTask->m_pAssetObject = new T();
	pTask->m_pCustomData = a_pCustomData;
	pTask->m_strFilePath = a_strFilePath;

	EAssetType eType = pTask->m_pAssetObject->GetAssetType();
	switch (eType)
	{
	case EAT_MESH:
	{
		pTask->m_eTaskType = ELATT_LOAD_MESH;
	}
	break;
	case EAT_TEXTURE:
	{
		pTask->m_eTaskType = ELATT_LOAD_TEXTURE;
	}
	break;
	case EAT_MATERIAL:
	{
		pTask->m_eTaskType = ELATT_LOAD_MATERIAL;
	}
	break;
	case EAT_ANIMATION:
	{
		pTask->m_eTaskType = ELATT_LOAD_ANIMATION;
	}
	break;
	default:
		break;
	}
}
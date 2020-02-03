#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::CResourceManager()
{
	this->m_pResourceLoader = NULL;
	this->m_mapID2Mesh.clear();
}

CResourceManager::~CResourceManager()
{
	if (this->m_pResourceLoader != NULL)
	{
		delete this->m_pResourceLoader;
		this->m_pResourceLoader = NULL;
	}

	hash_map<EModelID, CMesh*>::iterator iter = this->m_mapID2Mesh.begin();
	for (; iter != this->m_mapID2Mesh.end(); iter++)
	{
		delete iter->second;
	}
	this->m_mapID2Mesh.clear();
}

tbool CResourceManager::Init()
{
	this->m_pResourceLoader = new CResourceLoader();

	// Load Meshes
	this->LoadMesh(E_MODEL_ID_SKYBOX, "../Assets/Models/BaseModels/SkyBox.ply");
	this->LoadMesh(E_MODEL_ID_SHIP, "../Assets/Models/SM_Ship_Massive_Transport_01.ply");

	return true;
}

CMesh* CResourceManager::LoadMesh(EModelID a_eModeID, const tcchar* a_strFileName)
{
	CMesh* pOldMesh = this->FindMesh(a_eModeID);
	if (pOldMesh != NULL)
	{
		return pOldMesh;
	}
	CMesh* pMesh = new CMesh();
	this->m_pResourceLoader->LoadMesh(a_strFileName, pMesh);
	this->m_mapID2Mesh[a_eModeID] = pMesh;
	return pMesh;
}

CMesh* CResourceManager::FindMesh(EModelID a_eModeID)
{
	hash_map<EModelID, CMesh*>::iterator iter = this->m_mapID2Mesh.find(a_eModeID);
	if (iter == this->m_mapID2Mesh.end())
	{
		return NULL;
	}
	return iter->second;
}

void CResourceManager::DeleteMesh(EModelID a_eModeID)
{
	hash_map<EModelID, CMesh*>::iterator iter = this->m_mapID2Mesh.find(a_eModeID);
	if (iter == this->m_mapID2Mesh.end())
	{
		return;
	}
	CMesh* pMesh = iter->second;
	delete pMesh;
	this->m_mapID2Mesh.erase(a_eModeID);
}

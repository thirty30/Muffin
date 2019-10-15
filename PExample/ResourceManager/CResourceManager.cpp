#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::CResourceManager()
{
	this->m_pResourceLoader = NULL;
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
	this->m_mapID2Mesh.clear();

	this->LoadMesh(E_MODEL_ID_CUBE, "../Assets/Models/Cube.ply");
	this->LoadMesh(E_MODEL_ID_SPHERE, "../Assets/Models/Sphere.ply");
	this->LoadMesh(E_MODEL_ID_TERRAIN, "../Assets/Models/Terrain.ply");

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
	this->m_pResourceLoader->LoadModelFromPly(a_strFileName, pMesh);
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



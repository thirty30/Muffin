#pragma once

class CResourceManager : public CSingleton<CResourceManager>
{
public:
	hash_map<EModelID, CMesh*> m_mapID2Mesh;

public:
	CResourceManager();
	~CResourceManager();

	tbool Init();

	CMesh* LoadMesh(EModelID a_eModeID, const tcchar* a_strFileName);
	CMesh* FindMesh(EModelID a_eModeID);
	void DeleteMesh(EModelID a_eModeID);
};


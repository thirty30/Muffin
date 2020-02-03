#pragma once
#include "TMuffinSysInclude.h"

class CMesh;
class T_DLL_EXPORT CResourceLoader
{
public:
	tbool LoadModelFromPly(const tcchar* a_strFileName, CMesh* a_pMesh);
	tbool LoadModelFromPlyUV(const tcchar* a_strFileName, CMesh* a_pMesh);

	tbool LoadMesh(const tcchar* a_strFileName, CMesh* a_pMesh);
};


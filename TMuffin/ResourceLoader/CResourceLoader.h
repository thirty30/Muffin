#pragma once
#include "TMuffinSysInclude.h"
#include <Thread>
class CMesh;
class T_DLL_EXPORT CResourceLoader
{
public:
	tbool LoadModelFromPly(const tcchar* a_strFileName, CMesh* a_pMesh);	//discarded function
	tbool LoadModelFromPlyUV(const tcchar* a_strFileName, CMesh* a_pMesh);	//discarded function
	static tbool LoadMesh(const tcchar* a_strFileName, CMesh* a_pMesh);

};


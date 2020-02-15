#pragma once
#include "TMuffinSysInclude.h"

class CMesh;
class T_DLL_EXPORT CResourceLoader
{
public:
	static tbool LoadModelFromPly(const tcchar* a_strFileName, CMesh* a_pMesh);		//discarded function
	static tbool LoadModelFromPlyUV(const tcchar* a_strFileName, CMesh* a_pMesh);	//discarded function
	static tbool LoadMesh(const tcchar* a_strFileName, CMesh* a_pMesh);

};


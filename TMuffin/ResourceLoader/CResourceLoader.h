#pragma once

class T_DLL_EXPORT CResourceLoader
{
public:
	tbool LoadModelFromPly(const tcchar* a_strFileName, CMesh* a_pMesh);
	tbool LoadModelFromPlyUV(const tcchar* a_strFileName, CMesh* a_pMesh);

	tbool LoadTextureFromBMP(const tcchar* a_strFileName, CTexture* a_pTexture);
};


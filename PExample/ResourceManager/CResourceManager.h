#pragma once

class CResourceManager : public CSingleton<CResourceManager>
{
private:
	CResourceLoader* m_pResourceLoader;

	hash_map<EModelID, CMesh*> m_mapID2Mesh;
	hash_map<EShaderID, CShaderProgram*> m_mapID2Shader;
	hash_map<ETextureID, CTexture*> m_mapID2Texture;
	hash_map<EMaterialID, CMaterialBase*> m_mapID2Material;

public:
	CResourceManager();
	~CResourceManager();

	tbool Init();

	CMesh* LoadMesh(EModelID a_eModeID, const tcchar* a_strFileName, tbool a_bWithUV = false);
	CMesh* FindMesh(EModelID a_eModeID);
	void DeleteMesh(EModelID a_eModeID);

	CShaderProgram* LoaderShader(EShaderID a_eShaderID, const tcchar* a_strVertexShaderFile, const tcchar* a_strFragmentShaderFile);
	CShaderProgram* GetShaderProgram(EShaderID a_eShaderID);
	n32 GetShaderID(EShaderID a_eShaderID);

	CTexture* LoadTexture(ETextureID a_eTextureID, const tcchar* a_strFileName);
	CTexture* FindTexture(ETextureID a_eTextureID);

	CMaterialBase* LoadMaterial(EMaterialID a_eMaterialID, EShaderID a_eShaderID);
	CMaterialBase* FindMaterial(EMaterialID a_eMaterialID);
};


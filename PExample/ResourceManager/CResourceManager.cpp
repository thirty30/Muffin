#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::CResourceManager()
{
	this->m_pResourceLoader = NULL;
	this->m_mapID2Mesh.clear();
	this->m_mapID2Shader.clear();
	this->m_mapID2Texture.clear();
	this->m_mapID2Material.clear();
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
	this->LoadMesh(E_MODEL_ID_CUBE, "../Assets/Models/Cube.ply");
	this->LoadMesh(E_MODEL_ID_SPHERE, "../Assets/Models/Sphere.ply");
	this->LoadMesh(E_MODEL_ID_TRIANGLE, "../Assets/Models/Triangel_Particle2UV.ply", true);
	this->LoadMesh(E_MODEL_ID_SPHERE_UV, "../Assets/Models/SphereUV.ply", true);
	this->LoadMesh(E_MODEL_ID_CUBE_UV, "../Assets/Models/CubeUV.ply", true);
	this->LoadMesh(E_MODEL_ID_SKYBOX, "../Assets/Models/BaseModels/SkyBox.ply", true);
	this->LoadMesh(E_MODEL_ID_BUNNY_UV, "../Assets/Models/BunnyUV.ply", true);
	this->LoadMesh(E_MODEL_ID_SHIP, "../Assets/Models/SM_Ship_Stealth_03.ply", true);
	//this->LoadMesh(E_MODEL_ID_SPACESTATION, "../Assets/Models/SpaceStation.ply");
	this->LoadMesh(E_MODEL_ID_WATER, "../Assets/Models/water.ply");

	// Load Shaders
	this->LoaderShader(E_SHADER_ID_DEFAULT, "../Assets/shaders/DefaultVertexShader.glsl", "../Assets/shaders/DefaultFragmentShader.glsl");
	this->LoaderShader(E_SHADER_ID_STANDARD, "../Assets/shaders/StandardVertexShader.glsl", "../Assets/shaders/StandardFragmentShader.glsl");
	this->LoaderShader(E_SHADER_ID_SKYBOX, "../Assets/shaders/SkyBoxVertexShader.glsl", "../Assets/shaders/SkyBoxFragmentShader.glsl");
	this->LoaderShader(E_SHADER_ID_BUNNY, "../Assets/shaders/BunnyVertexShader.glsl", "../Assets/shaders/BunnyFragmentShader.glsl");
	this->LoaderShader(E_SHADER_ID_BILLBOARD, "../Assets/shaders/BillBoardVertexShader.glsl", "../Assets/shaders/BillBoardFragmentShader.glsl");
	this->LoaderShader(E_SHADER_ID_SHIP, "../Assets/shaders/ShipVertexShader.glsl", "../Assets/shaders/ShipFragmentShader.glsl");
	this->LoaderShader(E_SHADER_ID_WATER, "../Assets/shaders/WaterVertexShader.glsl", "../Assets/shaders/WaterFragmentShader.glsl");

	// Load Texture
	this->LoadTexture(E_TEXTURE_ID_TEST, "../Assets/Textures/leaf.png");
	this->LoadTexture(E_TEXTURE_ID_TEST2, "../Assets/Textures/leaf2.png");
	this->LoadTexture(E_TEXTURE_ID_CIRCLE, "../Assets/Textures/circle.png");
	this->LoadTexture(E_TEXTURE_ID_TEST3, "../Assets/Textures/ring.png");
	this->LoadTexture(E_TEXTURE_ID_DIFFUSE, "../Assets/Textures/Diffuse.png");
	this->LoadTexture(E_TEXTURE_ID_FIREWORK, "../Assets/Textures/fire.png");
	this->LoadTexture(E_TEXTURE_ID_WATER, "../Assets/Textures/water.png");

	// Load Materials
	this->LoadMaterial(E_MATERIAL_ID_DEFAULT, E_SHADER_ID_DEFAULT);
	this->LoadMaterial(E_MATERIAL_ID_STANDARD, E_SHADER_ID_STANDARD);
	this->LoadMaterial(E_MATERIAL_ID_BUNNY, E_SHADER_ID_BUNNY);
	this->LoadMaterial(E_MATERIAL_ID_BILLBOARD, E_SHADER_ID_BILLBOARD);
	this->LoadMaterial(E_MATERIAL_ID_SHIP, E_SHADER_ID_SHIP);
	this->LoadMaterial(E_MATERIAL_ID_WATER, E_SHADER_ID_WATER);

	return true;
}

CMesh* CResourceManager::LoadMesh(EModelID a_eModeID, const tcchar* a_strFileName, tbool a_bWithUV)
{
	CMesh* pOldMesh = this->FindMesh(a_eModeID);
	if (pOldMesh != NULL)
	{
		return pOldMesh;
	}
	CMesh* pMesh = new CMesh();
	if (a_bWithUV == false)
	{
		this->m_pResourceLoader->LoadModelFromPly(a_strFileName, pMesh);
	}
	else
	{
		this->m_pResourceLoader->LoadModelFromPlyUV(a_strFileName, pMesh);
	}
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

CShaderProgram* CResourceManager::LoaderShader(EShaderID a_eShaderID, const tcchar* a_strVertexShaderFile, const tcchar* a_strFragmentShaderFile)
{
	if (a_eShaderID <= E_SHADER_ID_UNKNOWN || a_eShaderID >= E_SHADER_ID_MAX)
	{
		return NULL;
	}
	if (this->GetShaderProgram(a_eShaderID) != NULL)
	{
		return NULL;
	}
	CShader* pVertexShader = new CShader(E_SHADER_TYPE_VERTEX, a_strVertexShaderFile);
	if (pVertexShader->InitShader() == false)
	{
		return NULL;
	}

	CShader* pFragmentShader = new CShader(E_SHADER_TYPE_FRAGMENT, a_strFragmentShaderFile);
	if (pFragmentShader->InitShader() == false)
	{
		return NULL;
	}

	CShaderProgram* pShaderProgram = new CShaderProgram();
	if (CreateShaderProgram(pVertexShader, pFragmentShader, pShaderProgram) == false)
	{
		return NULL;
	}
	this->m_mapID2Shader[a_eShaderID] = pShaderProgram;
	return pShaderProgram;
}

CShaderProgram* CResourceManager::GetShaderProgram(EShaderID a_eShaderID)
{
	hash_map<EShaderID, CShaderProgram*>::iterator iter = this->m_mapID2Shader.find(a_eShaderID);
	if (iter == this->m_mapID2Shader.end())
	{
		return NULL;
	}
	return iter->second;
}

n32 CResourceManager::GetShaderID(EShaderID a_eShaderID)
{
	CShaderProgram* pProgram = this->GetShaderProgram(a_eShaderID);
	if (pProgram == NULL)
	{
		return -1;
	}
	return pProgram->m_nOpenGLID;
}

CTexture* CResourceManager::LoadTexture(ETextureID a_eTextureID, const tcchar* a_strFileName)
{
	CTexture* pTexture = this->FindTexture(a_eTextureID);
	if (pTexture == NULL)
	{
		pTexture = new CTexture();
		pTexture->LoadTexture(a_strFileName);
		this->m_mapID2Texture[a_eTextureID] = pTexture;
	}
	return pTexture;
}

CTexture* CResourceManager::FindTexture(ETextureID a_eTextureID)
{
	hash_map<ETextureID, CTexture*>::const_iterator iter = this->m_mapID2Texture.find(a_eTextureID);
	if (iter == this->m_mapID2Texture.end())
	{
		return NULL;
	}
	return iter->second;
}

CMaterialBase* CResourceManager::LoadMaterial(EMaterialID a_eMaterialID, EShaderID a_eShaderID)
{
	CMaterialBase* pMaterial = this->FindMaterial(a_eMaterialID);
	if (pMaterial != NULL)
	{
		return pMaterial;
	}

	if (a_eMaterialID == E_MATERIAL_ID_DEFAULT)
	{
		pMaterial = new CMaterialDefault();
	}
	else
	{
		pMaterial = new CMaterialStandard();
	}

	if (pMaterial == NULL)
	{
		return NULL;
	}
	n32 nShaderID = this->GetShaderID(a_eShaderID);
	if (nShaderID == -1)
	{
		return NULL;
	}
	pMaterial->SetShaderProgramID(nShaderID);
	pMaterial->Init();
	this->m_mapID2Material[a_eMaterialID] = pMaterial;
	return pMaterial;
}

CMaterialBase* CResourceManager::FindMaterial(EMaterialID a_eMaterialID)
{
	hash_map<EMaterialID, CMaterialBase*>::const_iterator iter = this->m_mapID2Material.find(a_eMaterialID);
	if (iter == this->m_mapID2Material.end())
	{
		return NULL;
	}
	return iter->second;
}


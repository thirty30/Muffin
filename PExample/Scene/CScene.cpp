#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;
	this->m_pSkyBox = NULL;

	this->pParticle = NULL;
	this->m_fLastTime = 0;
}

CScene::~CScene()
{

}

tbool CScene::Init()
{
	m_pCameraControl = new CCameraControl();
	return true;
}

u64 CScene::GenGUID()
{
	return (++this->m_nGUIDIdx);
}

tbool CScene::LoadScene()
{
	//initialize camera
	n32 nScreenWidth = CGame::GetSingleton().GetScreenWidth();
	n32 nScreenHigh = CGame::GetSingleton().GetScreenHigh();
	f32 fScreenRatio = 1.0f * nScreenWidth / nScreenHigh;
	this->m_pCamera = new CCamera(this->GenGUID(), 0.6f, fScreenRatio, 1.0f, 100000.0f);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 200, -280);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 5, -10);
	//this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.8f, 1.0f));

	this->m_pCamera->m_vPosition = glm::vec3(0, 0, -20);
	this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f));
	TMuffin_AddCamera(this->m_pCamera);

	//Mesh
	CMesh* pMeshCube = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_CUBE);
	CMesh* pMeshSphere = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE);
	CMesh* pMeshTerrain = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_TERRAIN);
	CMesh* pMeshTriangle = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_TRIANGLE);
	CMesh* pMeshSphereUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE_UV);
	CMesh* pMeshCubeUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_CUBE_UV);
	CMesh* pMeshTest = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_TEST);
	CMesh* pMeshSkyBox = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SKYBOX);
	CMesh* pMeshBunnyUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_BUNNY_UV);

	//SkyBox
	n32 nShaderSkyBox = CResourceManager::GetSingleton().GetShaderID(E_SHADER_ID_SKYBOX);
	this->m_pSkyBox = new CSkyBox();
	this->m_pSkyBox->Init(pMeshSkyBox, nShaderSkyBox,
		"../Assets/Textures/SkyBox/BlueSky/BlueSkyX.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegX.png",
		"../Assets/Textures/SkyBox/BlueSky/BlueSkyY.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegY.png",
		"../Assets/Textures/SkyBox/BlueSky/BlueSkyZ.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegZ.png");
	TMuffin_SetSkyBox(this->m_pSkyBox);

	//pSkyBox->LoadTextures("../Assets/Textures/SkyBox/Space/SpaceBox_right1_posX.bmp", "../Assets/Textures/SkyBox/Space/SpaceBox_left2_negX.bmp",
	//	"../Assets/Textures/SkyBox/Space/SpaceBox_top3_posY.bmp", "../Assets/Textures/SkyBox/space/SpaceBox_bottom4_negY.bmp",
	//	"../Assets/Textures/SkyBox/Space/SpaceBox_front5_posZ.bmp", "../Assets/Textures/SkyBox/space/SpaceBox_back6_negZ.bmp");

	//scene items
	CDirectionLight* pDirectionLight = new CDirectionLight();

	//CPointLight* pPointLight1 = new CPointLight();
	//pPointLight1->m_vPosition = glm::vec3(100.0f, -100.0f, 30.0f);
	//pPointLight1->m_fLinear = 0.01f;
	//pPointLight1->m_fDistanceCutOff = 1000.0f;

	CMaterialStandard* pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BILLBOARD);
	CTexture* pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_TEST3);
	pMaterial->AddTexture(pTexture);

	pParticle = TMuffin_CreateParticleEmitter();
	pParticle->m_vPosition = glm::vec3(0, 0, 0);
	pParticle->m_vMinScale = glm::vec3(1.0f, 1.0f, 1.0f);
	pParticle->m_vMaxScale = glm::vec3(1.0f, 1.0f, 1.0f);
	pParticle->m_vMinAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	pParticle->m_vMaxAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	pParticle->m_vMinVelocity = glm::vec3(-2.0f, -2.0f, -2.0f);
	pParticle->m_vMaxVelocity = glm::vec3(2.0f, 2.0f, 2.0f);
	pParticle->m_vMinDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	pParticle->m_vMaxDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	pParticle->m_vMinColor = glm::vec4(0.9f, 0.39f, 0.13f, 1.0f);
	pParticle->m_vMaxColor = glm::vec4(0.9f, 0.129f, 0.058f, 1.0f);
	pParticle->m_fMinLifeTime = 5.0f;
	pParticle->m_fMaxLifeTime = 5.0f;
	pParticle->m_nMinEmitCount = 10;
	pParticle->m_nMaxEmitCount = 20;
	pParticle->m_fEmitPeriod = 0.5f;
	pParticle->m_pMesh = pMeshTriangle;
	pParticle->m_pMaterial = pMaterial;
	pParticle->SetParticleMode(E_PARTICLE_MODE_BILLBOARD);
	pParticle->SetCameraPosition(this->m_pCamera->m_vPosition);
	pParticle->InitializeEmitter();
	//pParticle->m_bEnable = false;

	return true;
}

void CScene::Clear()
{
	if (this->m_pCamera != NULL)
	{
		delete this->m_pCamera;
	}
	if (this->m_pCameraControl != NULL)
	{
		delete this->m_pCameraControl;
	}
}

void CScene::Loop()
{

}



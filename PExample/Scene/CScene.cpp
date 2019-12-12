#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;
	this->m_pSkyBox = NULL;
	this->m_mapID2Actor.clear();
}

CScene::~CScene()
{

}

tbool CScene::Init()
{
	this->m_pCameraControl = new CCameraControl();
	this->m_pShipControl = new CShipControl();
	return true;
}

n32 CScene::GenGUID()
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
	this->m_pCamera->m_vPosition = glm::vec3(0, 300, -300);
	this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.5f, 0.5f));
	TMuffin_AddCamera(this->m_pCamera);
	
	//SkyBox
	CMesh* pMeshSkyBox = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SKYBOX);
	this->m_pSkyBox = new CSkyBox();
	this->m_pSkyBox->Init(pMeshSkyBox, 
		"../Assets/Shaders/SkyBoxVertexShader.glsl", "../Assets/Shaders/SkyBoxFragmentShader.glsl",
		"../Assets/Textures/SkyBox/Space/SpaceBoxX.png", "../Assets/Textures/SkyBox/Space/SpaceBoxNegX.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxY.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegY.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxZ.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegZ.png"
		);
	TMuffin_SetSkyBox(this->m_pSkyBox);

	//scene items
	CDirectionLight* pDirectionLight = new CDirectionLight();

	CMesh* pMeshShip = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SHIP);
	CActor* pShip = new CActor();
	CMaterial* pMaterial = new CMaterial();
	pMaterial->Init("../Assets/Materials/StandardMaterial.json");
	pShip->InitRenderer(pMeshShip, pMaterial);

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

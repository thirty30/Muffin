#include "stdafx.h"

CScene1::CScene1(n32 a_nSceneID) : CSceneBase(a_nSceneID)
{
	this->pCameraObject = NULL;
}

CScene1::~CScene1()
{

}

tbool CScene1::Init()
{
	return true;
}

tbool CScene1::LoadScene()
{
	//Initialize Camera
	{
		n32 nScreenWidth = CGame::GetSingleton().GetScreenWidth();
		n32 nScreenHigh = CGame::GetSingleton().GetScreenHigh();
		f32 fScreenRatio = 1.0f * nScreenWidth / nScreenHigh;

		this->pCameraObject = new CGameObject();
		CCamera* pCamera = static_cast<CCamera*>(this->pCameraObject->AddComponent<CCamera>());
		pCamera->m_fFieldOfViewRadians = 0.6f;
		pCamera->m_fScreenRatio = fScreenRatio;
		pCamera->m_fViewDisBegin = 1.0f;
		pCamera->m_fViewDisEnd = 100000.0f;
		pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.3f, 0.7f));
		this->pCameraObject->GetTransform().m_vPosition = glm::vec3(0, 50, -100);

		CCameraControl* pController = static_cast<CCameraControl*>(CGame::GetSingleton().GetControlManager()->CreateController<CCameraControl>());
		pController->SetCamera(pCamera);
		pController->m_fCameraYMoveSpeed = 5.0f;
		pController->m_fCameraXMoveSpeed = 5.0f;
		pController->m_fCameraRotationSpeed = 1.0f;
		pController->m_fCameraScrollSpeed = 10.0f;
	}

	//SkyBox
	//TMuffin_SetSkyBox("../Assets/Models/BaseModels/SkyBox.ply",
	//	"../Assets/Shaders/SkyBoxVertexShader.glsl", "../Assets/Shaders/SkyBoxFragmentShader.glsl",
	//	"../Assets/Textures/SkyBox/Space/SpaceBoxX.png", "../Assets/Textures/SkyBox/Space/SpaceBoxNegX.png",
	//	"../Assets/Textures/SkyBox/Space/SpaceBoxY.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegY.png",
	//	"../Assets/Textures/SkyBox/Space/SpaceBoxZ.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegZ.png"
	//); 
	
	TMuffin_SetSkyBox("../Assets/Models/BaseModels/SkyBox.ply",
		"../Assets/Shaders/SkyBoxVertexShader.glsl", "../Assets/Shaders/SkyBoxFragmentShader.glsl",
		"../Assets/Textures/SkyBox/BlueSky/BlueSkyX.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegX.png",
		"../Assets/Textures/SkyBox/BlueSky/BlueSkyY.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegY.png",
		"../Assets/Textures/SkyBox/BlueSky/BlueSkyZ.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegZ.png"
	);

	//Scene Light
	CGameObject* pLight = new CGameObject();
	pLight->AddComponent<CDirectionLight>();

	CGameObject* pObj = new CGameObject();
	CParticleEmitter* pEmitter = pObj->AddComponent<CParticleEmitter>();
	pEmitter->m_pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/Cube.ply");
	pEmitter->m_pMaterial = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json");
	pEmitter->m_pMaterial->SetParam(0, 1.0f, 0.3f, 0.0f, 1.0f);
	pEmitter->m_vMinScale = glm::vec3(0.8f, 0.8f, 0.8f);
	pEmitter->m_vMaxScale = glm::vec3(1.2f, 1.2f, 1.2f);
	pEmitter->m_vMinAcceleration = glm::vec3(0, 5, 0);
	pEmitter->m_vMaxAcceleration = glm::vec3(0, 8, 0);
	pEmitter->m_vMinVelocity = glm::vec3(-3, 13, 0);
	pEmitter->m_vMaxVelocity = glm::vec3(3, 15, 0);
	pEmitter->m_vMinDeltaPosition = glm::vec3(-2.0f, -0.5f, -1.0f);
	pEmitter->m_vMaxDeltaPosition = glm::vec3(2.0f, 0.5f, 1.0f);
	pEmitter->m_fMinLifeTime = 0.3f;
	pEmitter->m_fMaxLifeTime = 0.7f;
	pEmitter->m_fEmitPeriod = 0.2f;
	pEmitter->m_nMinEmitCount = 10;
	pEmitter->m_nMaxEmitCount = 15;


	CGameObject* pObj2 = new CGameObject();
	CParticleEmitter* pEmitter2 = pObj2->AddComponent<CParticleEmitter>();
	pEmitter2->m_pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/Cube.ply");
	pEmitter2->m_pMaterial = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json");
	pEmitter2->m_pMaterial->SetParam(0, 1.0f, 0.8f, 0.0f, 1.0f);
	pEmitter2->m_vMinScale = glm::vec3(0.8f, 0.8f, 0.8f);
	pEmitter2->m_vMaxScale = glm::vec3(1.2f, 1.2f, 1.2f);
	pEmitter2->m_vMinAcceleration = glm::vec3(0, 3, 0);
	pEmitter2->m_vMaxAcceleration = glm::vec3(0, 5, 0);
	pEmitter2->m_vMinVelocity = glm::vec3(0, 5, 0);
	pEmitter2->m_vMaxVelocity = glm::vec3(0, 8, 0);
	pEmitter2->m_vMinDeltaPosition = glm::vec3(-1.2f, -0.5f, -1.4f);
	pEmitter2->m_vMaxDeltaPosition = glm::vec3(1.2f, 0.5f, 1.4f);
	pEmitter2->m_fMinLifeTime = 0.3f;
	pEmitter2->m_fMaxLifeTime = 0.5f;
	pEmitter2->m_fEmitPeriod = 0.2f;
	pEmitter2->m_nMinEmitCount = 3;
	pEmitter2->m_nMaxEmitCount = 5;

	this->LoadSceneFile("../Assets/Scene/Scene1.json");

	return true;
}

void CScene1::ReleaseScene()
{
	if (this->pCameraObject != NULL)
	{
		delete 	this->pCameraObject;
	}
}

void CScene1::Clear()
{

}

void CScene1::Loop()
{

}

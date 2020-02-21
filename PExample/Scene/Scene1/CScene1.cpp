#include "stdafx.h"


CScene1::CScene1(n32 a_nSceneID) : CSceneBase(a_nSceneID)
{
	this->pCameraObject = NULL;
	this->m_pSkyBox = NULL;
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
		pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.5f, 0.5f));
		this->pCameraObject->GetTransform().m_vPosition = glm::vec3(0, 10, -10);

		CCameraControl* pController = static_cast<CCameraControl*>(CGame::GetSingleton().GetControlManager()->CreateController<CCameraControl>());
		pController->SetCamera(pCamera);
		pController->m_fCameraYMoveSpeed = 0.2f;
		pController->m_fCameraXMoveSpeed = 0.4f;
		pController->m_fCameraRotationSpeed = 1.0f;
		pController->m_fCameraScrollSpeed = 2.0f;
	}

	//SkyBox
	CMesh* pMeshSkyBox = new CMesh();
	CResourceLoader::LoadMesh("../Assets/Models/BaseModels/SkyBox.ply", pMeshSkyBox);
	this->m_pSkyBox = new CSkyBox();
	this->m_pSkyBox->Init(pMeshSkyBox, 
		"../Assets/Shaders/SkyBoxVertexShader.glsl", "../Assets/Shaders/SkyBoxFragmentShader.glsl",
		"../Assets/Textures/SkyBox/Space/SpaceBoxX.png", "../Assets/Textures/SkyBox/Space/SpaceBoxNegX.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxY.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegY.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxZ.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegZ.png"
		);
	TMuffin_SetSkyBox(this->m_pSkyBox);

	//Scene Light
	CDirectionLight* pDirectionLight = new CDirectionLight();


	//Scene Items
	CGameObject* pRobot = new CGameObject();
	//pRobot->GetTransform().m_vScale = glm::vec3(1, 1, 1);
	//pRobot->GetTransform().SetRotation(glm::vec3(-90, 0, 0));
	CGraphicsComponent* pGraphics = static_cast<CGraphicsComponent*>(pRobot->AddComponent<CGraphicsComponent>());
	CMesh* pMesh = new CMesh();
	CResourceLoader::LoadMesh("../Assets/Models/Robot.fbx", pMesh);
	CMaterial* pMat = new CMaterial();
	pMat->Init("../Assets/Materials/RobotMaterial.json");
	pGraphics->InitRenderer(pMesh, pMat);
	CAnimator* pAnimator = static_cast<CAnimator*>(pRobot->AddComponent<CAnimator>());
	pAnimator->CreateAnimation("run", "../Assets/Animation/Robot/Run.fbx", pMesh);
	pAnimator->CreateAnimation("attack", "../Assets/Animation/Robot/Attack.fbx", pMesh);
	pAnimator->SetCurrentAnimation("run");
	delete pMesh;

	//this->LoadSceneFile("../Assets/Scene/Scene1.json");

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

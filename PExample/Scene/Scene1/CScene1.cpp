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
		pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.62f, 0.5f));
		this->pCameraObject->GetTransform().m_vPosition = glm::vec3(0, 30, -30);

		CCameraControl* pController = static_cast<CCameraControl*>(CGame::GetSingleton().GetControlManager()->CreateController<CCameraControl>());
		pController->SetCamera(pCamera);
		pController->m_fCameraYMoveSpeed = 1.0f;
		pController->m_fCameraXMoveSpeed = 1.0f;
		pController->m_fCameraRotationSpeed = 1.0f;
		pController->m_fCameraScrollSpeed = 5.0f;
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

	/*
	CGameObject* pObj = new CGameObject();
	pObj->GetTransform().m_vPosition = glm::vec3(-1.7f, 2, -1.8);
	CParticleEmitter* pEmitter = pObj->AddComponent<CParticleEmitter>();
	pEmitter->m_pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Cube.ply");
	pEmitter->m_pMaterial = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json");
	pEmitter->m_pMaterial->SetParam(0, 1.0f, 0.3f, 0.0f, 1.0f);
	pEmitter->m_vMinScale = glm::vec3(0.04f, 0.04f, 0.04f);
	pEmitter->m_vMaxScale = glm::vec3(0.06f, 0.06f, 0.06f);
	pEmitter->m_vMinAcceleration = glm::vec3(0, 0.5, 0);
	pEmitter->m_vMaxAcceleration = glm::vec3(0, 0.8, 0);
	pEmitter->m_vMinVelocity = glm::vec3(-0.3, 1.3, 0);
	pEmitter->m_vMaxVelocity = glm::vec3(0.3, 1.5, 0);
	pEmitter->m_vMinDeltaPosition = glm::vec3(-0.16f, -0.05f, -0.16f);
	pEmitter->m_vMaxDeltaPosition = glm::vec3(0.16f, 0.05f, 0.16f);
	pEmitter->m_fMinLifeTime = 0.3f;
	pEmitter->m_fMaxLifeTime = 0.7f;
	pEmitter->m_fEmitPeriod = 0.15f;
	pEmitter->m_nMinEmitCount = 5;
	pEmitter->m_nMaxEmitCount = 10;

	CGameObject* pObj2 = new CGameObject();
	CParticleEmitter* pEmitter2 = pObj2->AddComponent<CParticleEmitter>();
	pObj2->GetTransform().m_vPosition = glm::vec3(-1.7f, 2, -1.8);
	pEmitter2->m_pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Cube.ply");
	pEmitter2->m_pMaterial = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json");
	pEmitter2->m_pMaterial->SetParam(0, 1.0f, 0.8f, 0.0f, 1.0f);
	pEmitter2->m_vMinScale = glm::vec3(0.04f, 0.04f, 0.04f);
	pEmitter2->m_vMaxScale = glm::vec3(0.07f, 0.07, 0.07);
	pEmitter2->m_vMinAcceleration = glm::vec3(0, 0.5, 0);
	pEmitter2->m_vMaxAcceleration = glm::vec3(0, 1, 0);
	pEmitter2->m_vMinVelocity = glm::vec3(0, 2, 0);
	pEmitter2->m_vMaxVelocity = glm::vec3(0, 2.5, 0);
	pEmitter2->m_vMinDeltaPosition = glm::vec3(-0.12f, -0.05f, -0.14f);
	pEmitter2->m_vMaxDeltaPosition = glm::vec3(0.12f, 0.05f, 0.14f);
	pEmitter2->m_fMinLifeTime = 0.2f;
	pEmitter2->m_fMaxLifeTime = 0.3f;
	pEmitter2->m_fEmitPeriod = 0.2f;
	pEmitter2->m_nMinEmitCount = 3;
	pEmitter2->m_nMaxEmitCount = 5;

	CGameObject* pObj3 = new CGameObject();
	pObj3->GetTransform().m_vPosition = glm::vec3(1.7f, 2, -1.8);
	CParticleEmitter* pEmitter3 = pObj3->AddComponent<CParticleEmitter>();
	pEmitter3->m_pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Cube.ply");
	pEmitter3->m_pMaterial = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json");
	pEmitter3->m_pMaterial->SetParam(0, 1.0f, 0.3f, 0.0f, 1.0f);
	pEmitter3->m_vMinScale = glm::vec3(0.04f, 0.04f, 0.04f);
	pEmitter3->m_vMaxScale = glm::vec3(0.06f, 0.06f, 0.06f);
	pEmitter3->m_vMinAcceleration = glm::vec3(0, 0.5, 0);
	pEmitter3->m_vMaxAcceleration = glm::vec3(0, 0.8, 0);
	pEmitter3->m_vMinVelocity = glm::vec3(-0.3, 1.3, 0);
	pEmitter3->m_vMaxVelocity = glm::vec3(0.3, 1.5, 0);
	pEmitter3->m_vMinDeltaPosition = glm::vec3(-0.16f, -0.05f, -0.16f);
	pEmitter3->m_vMaxDeltaPosition = glm::vec3(0.16f, 0.05f, 0.16f);
	pEmitter3->m_fMinLifeTime = 0.3f;
	pEmitter3->m_fMaxLifeTime = 0.7f;
	pEmitter3->m_fEmitPeriod = 0.15f;
	pEmitter3->m_nMinEmitCount = 5;
	pEmitter3->m_nMaxEmitCount = 10;

	CGameObject* pObj4 = new CGameObject();
	CParticleEmitter* pEmitter4 = pObj4->AddComponent<CParticleEmitter>();
	pObj4->GetTransform().m_vPosition = glm::vec3(1.7f, 2, -1.8);
	pEmitter4->m_pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Cube.ply");
	pEmitter4->m_pMaterial = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json");
	pEmitter4->m_pMaterial->SetParam(0, 1.0f, 0.8f, 0.0f, 1.0f);
	pEmitter4->m_vMinScale = glm::vec3(0.04f, 0.04f, 0.04f);
	pEmitter4->m_vMaxScale = glm::vec3(0.07f, 0.07, 0.07);
	pEmitter4->m_vMinAcceleration = glm::vec3(0, 0.5, 0);
	pEmitter4->m_vMaxAcceleration = glm::vec3(0, 1, 0);
	pEmitter4->m_vMinVelocity = glm::vec3(0, 2, 0);
	pEmitter4->m_vMaxVelocity = glm::vec3(0, 2.5, 0);
	pEmitter4->m_vMinDeltaPosition = glm::vec3(-0.12f, -0.05f, -0.14f);
	pEmitter4->m_vMaxDeltaPosition = glm::vec3(0.12f, 0.05f, 0.14f);
	pEmitter4->m_fMinLifeTime = 0.2f;
	pEmitter4->m_fMaxLifeTime = 0.3f;
	pEmitter4->m_fEmitPeriod = 0.2f;
	pEmitter4->m_nMinEmitCount = 3;
	pEmitter4->m_nMaxEmitCount = 5;

	CGameObject* pRole = new CGameObject();
	CGraphicsComponent* pRoleGraphics = pRole->AddComponent<CGraphicsComponent>();
	pRoleGraphics->SetMesh(CAssetsLoader::Load<CMesh>("../Assets/Models/Character.fbx"));
	pRoleGraphics->SetMaterial(CAssetsLoader::Load<CMaterial>("../Assets/Materials/CharacterMaterial.json"));
	CAnimator* pAnimator = pRole->AddComponent<CAnimator>();
	pAnimator->CreateAnimation("run", "../Assets/Animation/running.fbx");

	CGameObject* pCastle = new CGameObject();
	pCastle->GetTransform().SetRotation(glm::vec3(0, 180, 0));
	pCastle->GetTransform().m_vPosition.y = -0.1f;
	CGraphicsComponent* pGraphics = pCastle->AddComponent<CGraphicsComponent>();
	pGraphics->SetMesh(CAssetsLoader::Load<CMesh>("../Assets/Models/castle.fbx"));
	pGraphics->SetMaterial(CAssetsLoader::Load<CMaterial>("../Assets/Materials/CastleMaterial.json"));

	CGameObject* pGround = new CGameObject();
	//pGround->GetTransform().SetRotation(glm::vec3(90, 0, 180));
	pGround->GetTransform().m_vScale = glm::vec3(8, 0, 12);
	pGround->GetTransform().m_vPosition = glm::vec3(0, 0, -8.5);
	CGraphicsComponent* pG2 = pGround->AddComponent<CGraphicsComponent>();
	pG2->SetMesh(CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Plane.ply"));
	pG2->SetMaterial(CAssetsLoader::Load<CMaterial>("../Assets/Materials/GroundMaterial.json"));

	CGameObject* pSphere = new CGameObject();
	pSphere->GetTransform().m_vPosition.y = 8;
	CGraphicsComponent* pGraphics = pSphere->AddComponent<CGraphicsComponent>();
	pGraphics->SetMesh(CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Sphere.ply"));
	pGraphics->SetMaterial(CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json"));
	CPhysicsComponent* pPhySphere = pSphere->AddComponent<CPhysicsComponent>();
	CRigidBody* pRB1 = pPhySphere->GetPhysicsObj().CreateBody<CRigidBody>();
	CColliderSphere* pCS1 = pPhySphere->GetPhysicsObj().CreateCollider<CColliderSphere>();

	CGameObject* pPlane = new CGameObject();
	CPhysicsComponent* pPhyPlane = pPlane->AddComponent<CPhysicsComponent>();
	CRigidBody* pRB2 = pPhyPlane->GetPhysicsObj().CreateBody<CRigidBody>();
	CColliderPlane* pCS2 = pPhyPlane->GetPhysicsObj().CreateCollider<CColliderPlane>();
	pCS2->m_vDirection = glm::vec3(0, 1, 0);
	pCS2->m_fConstant = 0;

	CGameObject* pBox = new CGameObject();
	pBox->GetTransform().m_vPosition = glm::vec3(1.1f, 1, 0);
	CGraphicsComponent* pGraphics2 = pBox->AddComponent<CGraphicsComponent>();
	pGraphics2->SetMesh(CAssetsLoader::Load<CMesh>("../Assets/Models/BaseModels/Cube.ply"));
	pGraphics2->SetMaterial(CAssetsLoader::Load<CMaterial>("../Assets/Materials/ColorMaterial.json"));
	pGraphics2->GetMaterial()->SetParam(0, 0, 1, 0, 1);
	CPhysicsComponent* pPhyBox = pBox->AddComponent<CPhysicsComponent>();
	CRigidBody* pRB3 = pPhyBox->GetPhysicsObj().CreateBody<CRigidBody>();
	pRB3->m_bIsStatic = true;
	CColliderBox* pCS3 = pPhyBox->GetPhysicsObj().CreateCollider<CColliderBox>();

	*/

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

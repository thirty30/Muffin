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
		pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.3f, 0.7f));
		this->pCameraObject->GetTransform().m_vPosition = glm::vec3(0, 500, -1000);

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

	//Scene Items
	CMesh* pMesh = CAssetsLoader::Load<CMesh>("../Assets/Models/SM_Ship_Massive_Transport_01.fbx");
	CMaterial* pMat = CAssetsLoader::Load<CMaterial>("../Assets/Materials/ShipMaterial.json");

	CGameObject* pNew = new CGameObject();
	CGraphicsComponent* pGraphics = pNew->AddComponent<CGraphicsComponent>();
	pGraphics->InitRenderer(pMesh, pMat);

	this->pObj = new CGameObject();
	this->pObj->GetTransform().m_vPosition = glm::vec3(200, 0, 0);
	CAssetsLoader::LoadASync<CMesh>("../Assets/Models/SM_Ship_Massive_Transport_01.fbx", NULL, this->LoadAssetsCallBack);
	CAssetsLoader::LoadASync<CMaterial>("../Assets/Materials/ShipMaterial.json", NULL, this->LoadAssetsCallBack);

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
	this->pObj->GetTransform().m_vPosition += glm::vec3(0, 0, 1.0);
}

void CScene1::LoadAssetsCallBack(void* a_pCustomData, CAssetObject* a_pObject)
{
	CScene1* pScene = (CScene1*)CSceneManager::GetSingleton().GetCurrentScene();
	if (a_pObject->GetAssetType() == EAT_MESH)
	{
		pScene->pMesh = static_cast<CMesh*>(a_pObject);
	}
	if (a_pObject->GetAssetType() == EAT_MATERIAL)
	{
		pScene->pMat = static_cast<CMaterial*>(a_pObject);
	}
	if (pScene->pMesh != NULL && pScene->pMat != NULL)
	{
		CGraphicsComponent* pGraphics = pScene->pObj->AddComponent<CGraphicsComponent>();
		pGraphics->InitRenderer(pScene->pMesh, pScene->pMat);
	}
}

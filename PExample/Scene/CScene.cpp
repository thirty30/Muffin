#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;

	this->pTempParticle = NULL;
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
	this->m_pCamera = new CCamera(this->GenGUID(), 0.6f, fScreenRatio, 0.01f, 1000.0f);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 200, -280);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 40, -55);
	this->m_pCamera->m_vPosition = glm::vec3(0, 0, -55);
	//this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.8f, 1.0f));
	TMuffin_AddCamera(this->m_pCamera);

	//Shader
	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_LIGHT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;
	CShaderProgram* pShaderProDefault = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramDefaultID = pShaderProDefault->m_nOpenGLID;
	CShaderProgram* pShaderUV = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_LIGHT_TEXTURE);
	n32 nShaderProgramUVID = pShaderUV->m_nOpenGLID;

	//Mesh
	CMesh* pMeshCube = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_CUBE);
	CMesh* pMeshSphere = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_SPHERE);
	CMesh* pMeshTerrain = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_TERRAIN);
	CMesh* pMeshTriangle = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_TRIANGLE);
	CMesh* pMeshSphereUV = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_SPHERE_UV);

	//scene items
	CDirectionLight* pDirectionLight = new CDirectionLight();

	CPointLight* pPointLight1 = new CPointLight();
	pPointLight1->m_vPosition = glm::vec3(100.0f, -100.0f, 30.0f);
	pPointLight1->m_fLinear = 0.01f;
	pPointLight1->m_fDistanceCutOff = 1000.0f;

	//CPointLight* pPointLight2 = new CPointLight();
	//pPointLight2->m_vPosition = glm::vec3(-10.0f, -10.0f, 0.0f);
	//pPointLight2->m_fLinear = 0.01f;
	//pPointLight2->m_fDistanceCutOff = 1000.0f;

	CCubeActor* pActor1 = new CCubeActor();
	pActor1->m_vPosition = glm::vec3(0.0f, 6.0f, 0.0f);
	pActor1->InitRenderer(pMeshCube, nShaderProgramDefaultID);
	pActor1->SetRenderMode(E_RENDER_MODE_FILL);
	CRigidBody* pCubeRB = pActor1->CreateRigidBody();
	pCubeRB->m_bIsPassive = false;
	CBoxCollider* pCubeCollider = (CBoxCollider*)pActor1->CreateCollider(E_COLLIDER_TYPE_BOX);
	pCubeCollider->m_fElastic = 0.4f;

	CActor* pActor2 = new CActor();
	pActor2->m_vPosition = glm::vec3(-10.0f, 10.0f, 0.0f);
	pActor2->InitRenderer(pMeshSphere, nShaderProgramDefaultID);
	pActor2->SetRenderMode(E_RENDER_MODE_FILL);
	CRigidBody* pSphereRB = pActor2->CreateRigidBody();
	pSphereRB->m_bUseGravity = true;
	pSphereRB->m_bIsPassive = false;
	pSphereRB->m_vVelocity = glm::vec3(7.5f, -2.0f, 0.0f);
	CSphereCollider* pSphereCollider = (CSphereCollider*)pActor2->CreateCollider(E_COLLIDER_TYPE_SPHERE);

	CActor* pActor3 = new CActor();
	pActor3->m_vPosition = glm::vec3(10.0f, 10.0f, 0.0f);
	pActor3->InitRenderer(pMeshSphere, nShaderProgramDefaultID);
	pActor3->SetRenderMode(E_RENDER_MODE_FILL);
	CRigidBody* pHitRB = pActor3->CreateRigidBody();
	pHitRB->m_bUseGravity = true;
	pHitRB->m_bIsPassive = false;
	pHitRB->m_vVelocity = glm::vec3(-27.5f, -3.0f, 0.0f);
	CSphereCollider* pHitCollider = (CSphereCollider*)pActor3->CreateCollider(E_COLLIDER_TYPE_SPHERE);


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



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

	//Mesh
	CMesh* pMeshCube = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_CUBE);
	CMesh* pMeshSphere = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_SPHERE);
	CMesh* pMeshTerrain = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_TERRAIN);
	CMesh* pMeshTriangle = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_TRIANGLE);

	//scene items
	//CDirectionLight* pDirectionLight = new CDirectionLight();

	CPointLight* pPointLight1 = new CPointLight();
	pPointLight1->m_vPosition = glm::vec3(-100.0f, 100.0f, 30.0f);
	pPointLight1->m_fLinear = 0.01f;
	pPointLight1->m_fDistanceCutOff = 1000.0f;

	//CPointLight* pPointLight2 = new CPointLight();
	//pPointLight2->m_vPosition = glm::vec3(-10.0f, -10.0f, 0.0f);
	//pPointLight2->m_fLinear = 0.01f;
	//pPointLight2->m_fDistanceCutOff = 1000.0f;

	//CGameObject* pObjTerrain = new CGameObject();
	//CMeshRenderer* pMeshTerrainRenderer = pObjTerrain->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	//pMeshTerrainRenderer->m_vRGB = glm::vec3(1.0f, 1.0f, 1.0f);
	//pMeshTerrainRenderer->InitRenderer(pMeshTerrain, nShaderProgramID);
	//pMeshTerrainRenderer->SetRenderMode(E_RENDER_MODE_FILL);
	//pObjTerrain->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	//CMeshCollider* pTerrainCollider = pObjTerrain->AddComponent<CMeshCollider>(E_COMPONENT_MESH_COLLIDER);
	//pTerrainCollider->InitColliderMesh(pMeshTerrain);

	//CGameObject* pObjCube = new CGameObject();
	//CMeshRenderer* pMeshCubeRenderer = pObjCube->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	//pMeshCubeRenderer->InitRenderer(pMeshCube, nShaderProgramDefaultID);
	//pMeshCubeRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	//pObjCube->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	//CMeshCollider* pCubeCollider = pObjCube->AddComponent<CMeshCollider>(E_COMPONENT_MESH_COLLIDER);
	//pCubeCollider->InitColliderMesh(pMeshCube);

	CGameObject* pObjCube = new CGameObject();
	CMeshRenderer* pMeshCubeRenderer = pObjCube->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	pMeshCubeRenderer->InitRenderer(pMeshCube, nShaderProgramDefaultID);
	pMeshCubeRenderer->SetRenderMode(E_RENDER_MODE_FILL);
	pObjCube->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	CBoxCollider* pCubeCollider = pObjCube->AddComponent<CBoxCollider>(E_COMPONENT_BOX_COLLIDER);
	pCubeCollider->m_vCenter = pObjCube->m_vPosition;
	pCubeCollider->m_fElastic = 0.4f;
	
	CGameObject* pObjSphere = new CGameObject();
	pObjSphere->m_vPosition = glm::vec3(-10.0f, 10.0f, 0.0f);
	CMeshRenderer* pMeshSphereRenderer = pObjSphere->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	pMeshSphereRenderer->InitRenderer(pMeshSphere, nShaderProgramDefaultID);
	pMeshSphereRenderer->SetRenderMode(E_RENDER_MODE_FILL);
	CRigidBody* pSphereRB = pObjSphere->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	pSphereRB->m_bUseGravity = true;
	pSphereRB->m_bIsPassive = false;
	pSphereRB->m_vVelocity = glm::vec3(7.5f, -2.0f, 0.0f);
	CSphereCollider* pSphereCollider = pObjSphere->AddComponent<CSphereCollider>(E_COMPONENT_SPHERE_COLLIDER);
	pSphereCollider->m_vCenter = pObjSphere->m_vPosition;
	pSphereCollider->m_fElastic = 1.0f;

	CGameObject* pObjHit = new CGameObject();
	pObjHit->m_vPosition = glm::vec3(10.0f, 10.0f, 0.0f);
	CMeshRenderer* pMeshHitRenderer = pObjHit->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	pMeshHitRenderer->InitRenderer(pMeshSphere, nShaderProgramDefaultID);
	pMeshHitRenderer->SetRenderMode(E_RENDER_MODE_FILL);
	CRigidBody* pHitRB = pObjHit->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	pHitRB->m_bUseGravity = true;
	pHitRB->m_bIsPassive = false;
	pHitRB->m_vVelocity = glm::vec3(-27.5f, -3.0f, 0.0f);
	CSphereCollider* pHitCollider = pObjHit->AddComponent<CSphereCollider>(E_COMPONENT_SPHERE_COLLIDER);
	pHitCollider->m_vCenter = pObjHit->m_vPosition;
	pHitCollider->m_fElastic = 1.0f;

	//CGameObject* pPlane = new CGameObject();
	//pPlane->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	//CPlaneCollider* pPlaneC = pPlane->AddComponent<CPlaneCollider>(E_COMPONENT_PLANE_COLLIDER);
	//pPlaneC->m_eAxis = E_PLANE_COLLIDER_AXIS_Y;
	//pPlaneC->m_fPos = -1.0f;

	this->pTempParticle = TMuffin_CreateParticleEmitter();
	pTempParticle->m_vPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	pTempParticle->m_vMinScale = glm::vec3(1.0f, 1.0f, 1.0f);
	pTempParticle->m_vMaxScale = glm::vec3(1.0f, 1.0f, 1.0f);
	pTempParticle->m_vMinAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	pTempParticle->m_vMaxAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	pTempParticle->m_vMinVelocity = glm::vec3(-3.0f, 10.0f, 0.0f);
	pTempParticle->m_vMaxVelocity = glm::vec3(3.0f, 10.0f, 0.0f);
	pTempParticle->m_vMinDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	pTempParticle->m_vMaxDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	pTempParticle->m_vMinColor = glm::vec4(0.9f, 0.39f, 0.13f, 1.0f);
	pTempParticle->m_vMaxColor = glm::vec4(0.9f, 0.129f, 0.058f, 1.0f);
	pTempParticle->m_fMinLifeTime = 1.0f;
	pTempParticle->m_fMaxLifeTime = 2.0f;
	pTempParticle->m_nMinEmitCount = 5;
	pTempParticle->m_nMaxEmitCount = 8;
	pTempParticle->m_fEmitPeriod = 0.05f;
	pTempParticle->m_pMesh = pMeshTriangle;
	pTempParticle->m_nShaderID = nShaderProgramDefaultID;
	pTempParticle->InitializeEmitter();

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



#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;
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
	this->m_pCamera->m_vPosition = glm::vec3(0, 15, -30);
	TMuffin_AddCamera(this->m_pCamera);

	//Shader
	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;

	//Mesh
	CMesh* pMeshCube = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_CUBE);
	CMesh* pMeshSphere = CGame::GetSingleton().GetResourceManager()->FindMesh(E_MODEL_ID_SPHERE);

	//scene items
	CGameObject* pObjCube = new CGameObject();
	CMeshRenderer* pMeshCubeRenderer = pObjCube->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	pMeshCubeRenderer->InitRenderer(pMeshCube, nShaderProgramID);
	pMeshCubeRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	pObjCube->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	TMuffin_AddGameObjects(pObjCube);
	

	CGameObject* pObjSphere = new CGameObject();
	pObjSphere->m_vPosition = glm::vec3(0, 10, 0);
	CMeshRenderer* pMeshSphereRenderer = pObjSphere->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	pMeshSphereRenderer->InitRenderer(pMeshSphere, nShaderProgramID);
	pMeshSphereRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	CRigidBody* pSphereRB = pObjSphere->AddComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
	pSphereRB->m_bUseGravity = true;
	pSphereRB->m_bIsPassive = false;
	CSphereCollider* pSphereCollider = pObjSphere->AddComponent<CSphereCollider>(E_COMPONENT_SPHERE_COLLIDER);
	pSphereCollider->m_vCenter = pObjSphere->m_vPosition;
	TMuffin_AddGameObjects(pObjSphere);

	//CGameObject* pObjDebugSphere = new CGameObject();
	//pObjDebugSphere->m_vPosition = glm::vec3(0, 0, 0);
	//pObjDebugSphere->m_vScale = glm::vec3(0.1f, 0.1f, 0.1f);
	//CMeshRenderer* pMeshDebugRenderer = pObjDebugSphere->AddComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
	//pMeshDebugRenderer->m_vRGB = glm::vec3(1.0f, 0.0f, 0.0f);
	//pMeshDebugRenderer->SetRenderMode(E_RENDER_MODE_FILL);
	//pMeshDebugRenderer->InitRenderer(pMeshSphere, nShaderProgramID);
	//TMuffin_AddGameObjects(pObjDebugSphere);

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

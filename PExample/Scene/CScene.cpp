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
	this->m_pCamera->m_vPosition = glm::vec3(0, 10, -20);
	TMuffin_AddCamera(this->m_pCamera);

	//initialize items
	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;

	//CMesh* pMeshTerrain = CGame::GetSingleton().GetResourceManager()->LoadMesh(E_MODEL_ID_TERRAIN, "./Assets/Models/Terrain.ply");
	//CGameObject* pObjTerrain = new CGameObject(this->GenGUID());
	//pObjTerrain->m_vScale = glm::vec3(0.1f, 0.1f, 0.1f);
	//pObjTerrain->InitMeshRenderer(pMeshTerrain, nShaderProgramID);
	//TMuffin_AddGameObjects(pObjCube->GetGUID(), pObjTerrain);

	CMesh* pMeshCube = CGame::GetSingleton().GetResourceManager()->LoadMesh(E_MODEL_ID_CUBE, "./Assets/Models/Cube.ply");
	CGameObject* pObjCube = new CGameObject(this->GenGUID());
	pObjCube->InitMeshRenderer(pMeshCube, nShaderProgramID);
	pObjCube->m_pMeshRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	TMuffin_AddGameObjects(pObjCube->GetGUID(), pObjCube);

	CMesh* pMeshSphere = CGame::GetSingleton().GetResourceManager()->LoadMesh(E_MODEL_ID_SPHERE, "./Assets/Models/Sphere.ply");
	CGameObject* pObjSphere = new CGameObject(this->GenGUID());
	pObjSphere->m_vPosition = glm::vec3(0, 2, 0);
	pObjSphere->InitMeshRenderer(pMeshSphere, nShaderProgramID);
	pObjSphere->m_pMeshRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	TMuffin_AddGameObjects(pObjSphere->GetGUID(), pObjSphere);
	
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
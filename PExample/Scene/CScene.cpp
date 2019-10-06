#include "stdafx.h"

CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
}

CScene::~CScene()
{

}

tbool CScene::Init()
{
	m_pCameraControl = new CCameraControl();
	return true;
}

tbool CScene::LoadScene()
{
	//initialize camera
	n32 nScreenWidth = CGame::GetSingleton().GetScreenWidth();
	n32 nScreenHigh = CGame::GetSingleton().GetScreenHigh();
	f32 fScreenRatio = 1.0f * nScreenWidth / nScreenHigh;
	this->m_pCamera = new CCamera(0.6f, fScreenRatio, 0.01f, 1000.0f);
	this->m_pCamera->m_vPosition = glm::vec3(0, 20, -20);
	TMuffin_AddCamera(this->m_pCamera);

	//initialize items
	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;

	CResourceLoader* pResLoader = CGame::GetSingleton().GetResourceLoader();

	//CMesh* pMeshTerrain = new CMesh();
	//pResLoader->LoadModelFromPly("./Assets/Models/Terrain.ply", pMeshTerrain);
	//CGameObject* pObjTerrain = new CGameObject();
	//pObjTerrain->m_vScale = glm::vec3(0.1f, 0.1f, 0.1f);
	//pObjTerrain->InitMeshRenderer(pMeshTerrain, nShaderProgramID);
	//TMuffin_AddGameObjects(pObjTerrain);
	//delete pMeshTerrain;

	CMesh* pMeshCube = new CMesh();
	pResLoader->LoadModelFromPly("./Assets/Models/Cube.ply", pMeshCube);
	CGameObject* pObjCube = new CGameObject();
	pObjCube->InitMeshRenderer(pMeshCube, nShaderProgramID);
	pObjCube->m_pMeshRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	TMuffin_AddGameObjects(pObjCube);
	delete pMeshCube;

	CMesh* pMeshSphere = new CMesh();
	pResLoader->LoadModelFromPly("./Assets/Models/Sphere.ply", pMeshSphere);
	CGameObject* pObjSphere = new CGameObject();
	pObjSphere->m_vPosition = glm::vec3(0, 2, 0);
	pObjSphere->InitMeshRenderer(pMeshSphere, nShaderProgramID);
	pObjSphere->m_pMeshRenderer->SetRenderMode(E_RENDER_MODE_LINE);
	TMuffin_AddGameObjects(pObjSphere);
	delete pMeshSphere;

	
	return true;
}

void CScene::Clear()
{
	if (this->m_pCamera != NULL)
	{
		delete this->m_pCamera;
	}
}

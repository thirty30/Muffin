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
	TMuffin_AddCamera(this->m_pCamera);

	//initialize items
	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;

	CMesh* pMesh = new CMesh();
	CResourceLoader* pResMgr = new CResourceLoader();
	pResMgr->LoadModelFromPly("./Assets/models/bun_zipper_res4_xyz.ply", pMesh);

	CGameObject* pGameObj = new CGameObject();
	pGameObj->m_vPosition = glm::vec3(0, 0, 10);
	pGameObj->m_vScale = glm::vec3(6, 6, 6);
	pGameObj->InitMeshRenderer(pMesh, nShaderProgramID);
	TMuffin_AddGameObjects(pGameObj);

	CGameObject* pGameObj2 = new CGameObject();
	pGameObj2->m_vPosition = glm::vec3(4, 0, 10);
	pGameObj2->m_vScale = glm::vec3(6, 6, 6);
	pGameObj2->InitMeshRenderer(pMesh, nShaderProgramID);
	TMuffin_AddGameObjects(pGameObj2);

	delete pMesh;
	
	return true;
}

void CScene::Clear()
{
	if (this->m_pCamera != NULL)
	{
		delete this->m_pCamera;
	}
}

#include "stdafx.h"

tbool Init()
{
	CShaderManager* pShaderMgr = new CShaderManager();
	if (pShaderMgr->Init() == false)
	{
		return false;
	}

	return true;
}

n32 main(n32 argc, tcchar** argv)
{
	f32 fScreenWidth = 1600.0f;
	f32 fScreenHigh = 900.0f;
	if (InitMuffin() == false)
	{
		return 0;
	}
	if (InitMuffinWindow(fScreenWidth, fScreenHigh, "PExample") == false)
	{
		return 0;
	}

	if (Init() == false)
	{
		cout << "Initialize fail!" << endl;
		return false;
	}

	CCamera* pCamera = new CCamera();
	pCamera->m_fFieldOfViewRadians = 0.6f;
	pCamera->m_fViewDisBegin = 0.01f;
	pCamera->m_fViewDisEnd = 1000.0f;
	pCamera->m_fScreenRatio = fScreenWidth / fScreenHigh;
	TMuffin_AddCamera(pCamera);

	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;

	CMesh* pMesh = new CMesh();
	CResourceLoader* pResMgr = new CResourceLoader();
	pResMgr->LoadModelFromPly("./Assets/models/bun_zipper_res4_xyz.ply", pMesh);

	CGameObject* pGameObj = new CGameObject();
	pGameObj->m_vScale = glm::vec3(6, 6, 6);
	pGameObj->InitMeshRenderer(pMesh, nShaderProgramID);

	delete pMesh;
	TMuffin_AddGameObjects(pGameObj);

	LoopMuffin();
	ClearMuffin();
	return 0;
}


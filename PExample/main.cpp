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
	CWindow* pWindow = new CWindow(1600, 900, "PExample");
	pWindow->InitWindow();

	if (Init() == false)
	{
		cout << "Initialize fail!" << endl;
		return false;
	}

	CShaderProgram* pShaderPro = CShaderManager::GetSingleton().FindShaderProgramByCustomID(E_SHADER_ID_DEFAULT);
	n32 nShaderProgramID = pShaderPro->m_nOpenGLID;

	CVAOManager* pVAO = new CVAOManager();
	pVAO->LoadModel(E_MODEL_ID_BUNNY, "./Assets/models/bun_zipper_res4_xyz.ply", nShaderProgramID);

	CGameObject* pGameObj = new CGameObject();
	pGameObj->m_nShaderProgramID = nShaderProgramID;
	pGameObj->m_pDrawInfo = pVAO->FindModel(E_MODEL_ID_BUNNY);
	pGameObj->m_vPosition = glm::vec3(0, 0, 0);
	pGameObj->m_vScale = glm::vec3(6, 6, 6);

	TMuffin_RegisterGameObjects(pGameObj);

	pWindow->Loop();
	pWindow->Clear();
	return 0;
}


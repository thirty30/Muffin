#include "stdafx.h"

T_IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager() : m_GUIDMaker(1)
{
	this->m_vecScene.clear();
	this->m_nCurSceneID = -1;
}

CSceneManager::~CSceneManager()
{
	this->Clear();
}

tbool CSceneManager::Init()
{
	n32 nID = this->m_GUIDMaker.GenerateGUID(0);
	CSceneBase* pScene = new CScene1(nID);
	pScene->Init();
	this->AddScene(pScene);

	return true;
}

void CSceneManager::Clear()
{
	for (n32 i = 0; i < this->m_vecScene.size(); i++)
	{
		this->m_vecScene[i]->Clear();
		delete this->m_vecScene[i];
	}
	this->m_vecScene.clear();
}

void CSceneManager::AddScene(CSceneBase* a_pScene)
{
	this->m_vecScene.push_back(a_pScene);
}

CSceneBase* CSceneManager::GetCurrentScene()
{
	if (this->m_nCurSceneID >= 0 && this->m_nCurSceneID < this->m_vecScene.size())
	{
		return this->m_vecScene[this->m_nCurSceneID];
	}
	return NULL;
}

void CSceneManager::SwitchScene(n32 a_nSceneID)
{
	if (this->m_nCurSceneID >= 0 && this->m_nCurSceneID < this->m_vecScene.size())
	{
		this->m_vecScene[this->m_nCurSceneID]->ReleaseScene();
	}

	this->m_nCurSceneID = a_nSceneID;
	this->m_vecScene[this->m_nCurSceneID]->LoadScene();
}

void CSceneManager::Loop()
{
	for (n32 i = 0; i < this->m_vecScene.size(); i++)
	{
		this->m_vecScene[i]->Loop();
	}
}



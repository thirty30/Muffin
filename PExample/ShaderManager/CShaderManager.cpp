#include "stdafx.h"

T_IMPLEMENT_SINGLETON(CShaderManager)

tbool CShaderManager::Init()
{
	this->m_mapCustomID2Program.clear();
	tbool bRes = false;

	//Default Shader with light////////////////////////////////////////////////////
	CShader* pDefaultVertexShader = new CShader(E_SHADER_TYPE_VERTEX, "./Assets/shaders/DefaultVertexShader.glsl");
	bRes = pDefaultVertexShader->InitShader();
	if (bRes == false) { return false; }

	CShader* pDefaultFragmentShader = new CShader(E_SHADER_TYPE_FRAGMENT, "./Assets/shaders/DefaultFragmentShader.glsl");
	bRes = pDefaultFragmentShader->InitShader();
	if (bRes == false) { return false; }

	CShaderProgram* pDefaultShaderProgram = new CShaderProgram();
	bRes = CreateShaderProgram(pDefaultVertexShader, pDefaultFragmentShader, pDefaultShaderProgram);
	if (bRes == false) { return false; }

	this->m_mapCustomID2Program[E_SHADER_ID_DEFAULT] = pDefaultShaderProgram;

	//Other Shaders////////////////////////////////////////////////////
	
	return true;
}

void CShaderManager::Clear()
{
	hash_map<n32, CShaderProgram*>::iterator iter = this->m_mapCustomID2Program.begin();
	for (; iter != this->m_mapCustomID2Program.end(); iter++)
	{
		CShaderProgram* pPro = iter->second;
		if (pPro == NULL)
		{
			continue;
		}
		if (pPro->m_pVertexShader != NULL)
		{
			delete pPro->m_pVertexShader;
		}
		if (pPro->m_pFragmentShader != NULL)
		{
			delete pPro->m_pFragmentShader;
		}
		delete pPro;
	}
}

CShaderProgram* CShaderManager::FindShaderProgramByCustomID(n32 a_nCustomID)
{
	hash_map<n32, CShaderProgram*>::iterator iter = this->m_mapCustomID2Program.find(a_nCustomID);
	if (iter == this->m_mapCustomID2Program.end())
	{
		return NULL;
	}
	return iter->second;
}

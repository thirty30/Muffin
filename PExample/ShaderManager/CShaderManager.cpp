#include "stdafx.h"

T_IMPLEMENT_SINGLETON(CShaderManager)

tbool CShaderManager::Init()
{
	this->m_mapCustomID2Program.clear();

	CShader* pDefaultVertexShader = new CShader(E_SHADER_TYPE_VERTEX, "./Assets/shaders/DefaultVertexShader.glsl");
	if (pDefaultVertexShader->InitShader() == false) { return false; }

	CShader* pDefaultFragmentShader = new CShader(E_SHADER_TYPE_FRAGMENT, "./Assets/shaders/DefaultFragmentShader.glsl");
	if (pDefaultFragmentShader->InitShader() == false) { return false; }

	CShaderProgram* pDefaultShaderProgram = new CShaderProgram();
	CreateShaderProgram(pDefaultVertexShader, pDefaultFragmentShader, pDefaultShaderProgram);

	this->m_mapCustomID2Program[E_SHADER_ID_DEFAULT] = pDefaultShaderProgram;


	CShader* pTestVertexShader = new CShader(E_SHADER_TYPE_VERTEX, "./Assets/shaders/Test_VertexShader.glsl");
	if (pTestVertexShader->InitShader() == false) { return false; }

	CShader* pTestFragmentShader = new CShader(E_SHADER_TYPE_FRAGMENT, "./Assets/shaders/Test_FragmentShader.glsl");
	if (pTestFragmentShader->InitShader() == false) { return false; }

	CShaderProgram* pTestShaderProgram = new CShaderProgram();
	CreateShaderProgram(pTestVertexShader, pTestFragmentShader, pTestShaderProgram);

	this->m_mapCustomID2Program[E_SHADER_ID_TEST] = pTestShaderProgram;
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

#include "pch.h"

CLightManager::CLightManager()
{
	this->m_mapID2Light.clear();
	this->m_nGUIDIDX = 0;
}

CLightManager::~CLightManager()
{
	this->m_mapID2Light.clear();
}

void CLightManager::AddLight(CLight* a_pLight)
{
	a_pLight->m_nMuffinGUID = this->GetGUID();
	n32 nLightCount = this->m_mapID2Light.size();
	a_pLight->InitGLSLName(nLightCount);
	this->m_mapID2Light[a_pLight->m_nMuffinGUID] = a_pLight;
}

void CLightManager::DeleteLight(CLight* a_pLight)
{
	u64 nGUID = a_pLight->m_nMuffinGUID;
	CLight* pLight = this->FindLight(nGUID);
	if (pLight == NULL)
	{
		return;
	}
	this->m_mapID2Light.erase(nGUID);
}

CLight* CLightManager::FindLight(u64 a_nGUID)
{
	hash_map<u64, CLight*>::const_iterator iter = this->m_mapID2Light.find(a_nGUID);
	if (iter == this->m_mapID2Light.end())
	{
		return NULL;
	}
	return iter->second;
}

void CLightManager::RenderLights(n32 a_nShaderProgramID)
{
	GLint nLightNum = glGetUniformLocation(a_nShaderProgramID, "un_nLightNum");
	glUniform1i(nLightNum, this->m_mapID2Light.size());

	hash_map<u64, CLight*>::const_iterator iter = this->m_mapID2Light.begin();
	for (; iter != this->m_mapID2Light.end(); iter++)
	{
		CLight* pCurLight = iter->second;
		if (pCurLight == NULL)
		{
			continue;
		}
		pCurLight->InitShader(a_nShaderProgramID);
		pCurLight->BindShader(a_nShaderProgramID);
	}
}

#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	this->m_strFileName.clear();
	this->m_mapName2Animation.clear();
	this->m_pCurrentAnimation = NULL;
}

CAnimator::~CAnimator()
{
	this->m_strFileName.clear();
	hash_map<tstring, CAnimation*>::const_iterator iter = this->m_mapName2Animation.begin();
	for (; iter != this->m_mapName2Animation.end(); iter++)
	{
		delete iter->second;
	}
	this->m_mapName2Animation.clear();
	this->m_pCurrentAnimation = NULL;
}

void CAnimator::CreateAnimation(tstring a_strKey, const tcchar* a_pFileName, CMesh* a_pMesh)
{
	tstring strFileName(a_pFileName);
	CAnimation* pAnimation = new CAnimation();
	pAnimation->Init(a_pFileName, a_pMesh);
	this->m_mapName2Animation[a_strKey] = pAnimation;
}

CAnimation* CAnimator::GetAnimation(tstring a_strKey)
{
	hash_map<tstring, CAnimation*>::const_iterator iter = this->m_mapName2Animation.find(a_strKey);
	if (iter != this->m_mapName2Animation.end())
	{
		return iter->second;
	}
	return NULL;
}

void CAnimator::SetCurrentAnimation(tstring a_strKey)
{
	CAnimation* pAnimation = this->GetAnimation(a_strKey);
	if (pAnimation == NULL)
	{
		return;
	}
	this->m_pCurrentAnimation = pAnimation;
}


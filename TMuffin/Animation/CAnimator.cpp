#include "CAnimator.h"
#include "CAnimation.h"

void CAnimator::CallBackEndAnimation()
{
	if (this->m_pCallBack != NULL)
	{
		this->m_pCallBack(this->m_pCurrentAnimation->m_strName, this->m_pCallBackCustom);
	}
}

void CAnimator::Init()
{

}

CAnimator::CAnimator()
{
	this->m_strFileName.clear();
	this->m_mapName2Animation.clear();
	this->m_pCurrentAnimation = NULL;
	this->m_pCallBack = NULL;
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

CAnimation* CAnimator::CreateAnimation(tstring a_strKey, const tcchar* a_pFileName)
{
	tstring strFileName(a_pFileName);
	CAnimation* pAnimation = new CAnimation();
	pAnimation->m_strName = a_strKey;
	pAnimation->SetAnimator(this);
	pAnimation->Init(a_pFileName);
	this->m_mapName2Animation[a_strKey] = pAnimation;
	if (this->m_pCurrentAnimation == NULL)
	{
		this->m_pCurrentAnimation = pAnimation;
	}
	return pAnimation;
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
	if (this->m_pCurrentAnimation == pAnimation && this->m_pCurrentAnimation->IsPlaying() == true)
	{
		return;
	}
	this->m_pCurrentAnimation = pAnimation;
	this->m_pCurrentAnimation->Reset();
}

void CAnimator::SetCallBack(MuffinAnimationCallBack a_pCallBack, void* a_pCustom)
{
	this->m_pCallBack = a_pCallBack;
	this->m_pCallBackCustom = a_pCustom;
}

tbool CAnimator::IsPlaying()
{
	return this->m_pCurrentAnimation->IsPlaying();
}


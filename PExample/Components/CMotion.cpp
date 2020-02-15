#include "stdafx.h"

CMotion::CMotion()
{

}

CMotion::~CMotion()
{

}

void CMotion::Update()
{
	CTransform& rTrans = this->GetGameObject()->GetTransform();
	f32 fDT = TMuffin_GetDeltaFrameTime();
	rTrans.m_vPosition += this->m_vVelocity * fDT;
}


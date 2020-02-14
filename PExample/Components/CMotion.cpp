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

	rTrans.m_vPosition += glm::vec3(0, -20.0f, 20.0f) * fDT;
}


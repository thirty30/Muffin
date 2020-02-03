#pragma once
#include "TMuffinSysInclude.h"
#include "CLineTween.h"

class T_DLL_EXPORT CLineTweenMove : public CLineTween
{
private:
	glm::vec3 m_vStartPosition;
	glm::vec3 m_vEndPosition;
	f32 m_fNowTime;
	f32 m_fTargetTime;

	glm::vec3 m_vVelocity;
	glm::vec3 m_vMidVeloctiy;

	f32 m_fEaseTime;
	glm::vec3 m_vAcc;

	f32 m_fNowDis;
	f32 m_fEaseDis;
	f32 m_fTotalDis;

public:
	CLineTweenMove(u64 a_nID, CGameObject* a_pParent);
	~CLineTweenMove();
	virtual void Update();
	tbool Init(glm::vec3 a_vStartPosition, glm::vec3 a_vEndPosition, f32 a_fVelocity, f32 a_fEaseTime = 0);
};


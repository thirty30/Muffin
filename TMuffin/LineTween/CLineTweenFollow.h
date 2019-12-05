#pragma once

class T_DLL_EXPORT CLineTweenFollow : public CLineTween
{
private:
	CGameObject* m_pTargetObject;
	f32 m_fDistance;

	f32 m_fNowTime;
	f32 m_fTargetTime;
	f32 m_fVelocity;

public:
	CLineTweenFollow(u64 a_nID, CGameObject* a_pParent);
	~CLineTweenFollow();

	virtual void Update();
	tbool Init(CGameObject* a_pTarget, f32 a_fDistance, f32 a_fVelocity);
};


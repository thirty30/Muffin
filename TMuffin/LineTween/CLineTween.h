#pragma once

class CGameObject;
class T_DLL_EXPORT CLineTween
{
protected:
	u64 m_nLineTweenID;
	ELineTweenType m_eType;
	CGameObject* m_pParentObject;
	tbool m_bIsDone;
	tbool m_bIsEnable;

public:
	virtual void Update() T_PURE;

	CLineTween(u64 a_nID, CGameObject* a_pParent, ELineTweenType a_eType) :
		m_nLineTweenID(a_nID),
		m_eType(a_eType),
		m_pParentObject(a_pParent),
		m_bIsDone(false),
		m_bIsEnable(false)
	{
	}
	virtual ~CLineTween() {}
	virtual tbool IsDone() { return this->m_bIsDone; }

	u64 GetLineTweenID() { return this->m_nLineTweenID; }
	ELineTweenType GetAnimationType() { return this->m_eType; }
};


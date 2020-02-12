#pragma once
#include "TMuffinSysInclude.h"

class CGameObject;
class T_DLL_EXPORT CComponentBase
{
private:
	CGameObject* m_pGameObect;
	tbool m_bIsInit;
	friend class CGameObject;

protected:
	virtual void Init() {}
	virtual void Update() {}
	virtual void Clear() {}

public:
	CComponentBase()
	{
		this->m_pGameObect = NULL;
		this->m_bIsInit = false;
	}
	virtual ~CComponentBase()
	{
		this->m_pGameObect = NULL;
	}

	T_INLINE CGameObject* GetGameObject() { return this->m_pGameObect; }

};

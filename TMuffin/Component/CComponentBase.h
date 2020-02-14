#pragma once
#include "TMuffinSysInclude.h"

#define T_SCS void SetProperty(tstring a_strName, ...) { va_list parms; va_start(parms, a_strName);
#define T_SCE va_end(parms); }
#define T_SCP(p, t) if (a_strName == #p) { this->##p = va_arg(parms, t); }

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
	virtual void SetProperty(tstring a_strName, ...) {}
	T_INLINE CGameObject* GetGameObject() { return this->m_pGameObect; }

};

#pragma once
#include "TMuffinSysInclude.h"
#include "../TPhysics/TPhysics.h"

#define T_SCS void SetProperty(tstring a_strName, ...) { va_list parms; va_start(parms, a_strName);
#define T_SCE va_end(parms); }
#define T_SCP(p, t) if (a_strName == #p) { this->##p = va_arg(parms, t); }

class CGameObject;
class T_DLL_EXPORT CComponentBase
{
private:
	CGameObject* m_pGameObect;
	tbool m_bIsEnable;
	friend class CGameObject;

protected:
	virtual void Init() {}
	virtual void Update() {}
	virtual void Clear() {}
	virtual void OnCollider(const SCollisionInfo& a_rCollision) {}
	virtual void Disable() {}
	virtual void Enable() {}

public:
	CComponentBase()
	{
		this->m_pGameObect = NULL;
		this->m_bIsEnable = true;
	}
	virtual ~CComponentBase()
	{
		this->m_pGameObect = NULL;
	}
	virtual void SetProperty(tstring a_strName, ...) {}
	T_INLINE CGameObject* GetGameObject() { return this->m_pGameObect; }
	void SetEnable(tbool a_bValue) { this->m_bIsEnable = a_bValue; }
};

#include "stdafx.h"

CComponentBase* CreateLogicComponent(CGameObject* a_pObj, tstring a_strClassName)
{
#define REGISTER_COM(v) if (a_strClassName == #v) { return a_pObj->AddComponent<v>(); }

	REGISTER_COM(CMotion);

#undef  REGISTER_COM
	return NULL;
}


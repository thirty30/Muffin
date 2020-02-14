#include "stdafx.h"

extern CComponentBase* CreateComponent(CGameObject* a_pObj, tstring a_strClassName)
{
	T_REGISTER_COM(CGraphicsComponent)
	T_REGISTER_COM(CMotion)
}


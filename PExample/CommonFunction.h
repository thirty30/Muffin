#pragma once

#define T_REGISTER_COM(v) if (a_strClassName == #v) { return a_pObj->AddComponent<v>(); }
extern CComponentBase* CreateComponent(CGameObject* a_pObj, tstring a_strClassName);

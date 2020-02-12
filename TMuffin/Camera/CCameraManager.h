#pragma once
#include "TMuffinSysInclude.h"

class CCamera;
class T_DLL_EXPORT CCameraManager
{
private:
	CCamera* m_pSceneCamera;
public:
	CCameraManager();;
	~CCameraManager();;

	T_INLINE void AddCamera(CCamera* a_pCamera);
	T_INLINE void RemoveCamera(CCamera* a_pCamera);
	T_INLINE CCamera* GetTopCamera();
};




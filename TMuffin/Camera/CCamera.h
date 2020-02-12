#pragma once
#include "TMuffinSysInclude.h"
#include "Component/CComponentBase.h"

class CGameObject;
class T_DLL_EXPORT CCamera : public CComponentBase
{
public:
	f32 m_fFieldOfViewRadians;
	f32 m_fScreenRatio;
	f32 m_fViewDisBegin;
	f32 m_fViewDisEnd;
	glm::vec3 m_vTowards;
	glm::vec3 m_vUpwards;
	n32 m_nDepth;

protected:
	virtual void Init() override;

public:
	CCamera();
	~CCamera();

	T_INLINE glm::mat4 GetPerspective();
	T_INLINE glm::mat4 GetView();
};





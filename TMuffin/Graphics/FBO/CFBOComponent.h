#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "Component/CComponentBase.h"

class CCamera;
class CGraphicsComponent;
class T_DLL_EXPORT CFBOComponent : public CComponentBase
{
private:
	GLuint m_nFBOID;
	GLuint m_nColorTextureID;
	GLuint m_nDepthTextureID;
	CGameObject* m_pCameraObject;
	CGraphicsComponent* m_pGraphics;
	friend class CGraphicsWorld;
	
public:
	n32 m_nWidthSize;
	n32 m_nHeightSize;
	f32 m_fFieldOfViewRadians;
	f32 m_fScreenRatio;
	f32 m_fViewDisBegin;
	f32 m_fViewDisEnd;
	glm::vec3 m_vCameraPosition;
	glm::vec3 m_vTowards;

	T_SCS
		T_SCP(m_nWidthSize, n32)
		T_SCP(m_nHeightSize, n32)
		T_SCP(m_fFieldOfViewRadians, f64)
		T_SCP(m_fScreenRatio, f64)
		T_SCP(m_fViewDisBegin, f64)
		T_SCP(m_fViewDisEnd, f64)
		T_SCP(m_vCameraPosition, glm::vec3)
		T_SCP(m_vTowards, glm::vec3)
	T_SCE

public:
	CFBOComponent();
	~CFBOComponent();

	virtual void Init() override;
	virtual void Clear() override;
	void BindBuffer();
	void ReleaseBuffer();
	T_INLINE CCamera* GetCamera();
};

#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "Component/IComponent.h"

class CLineTween;
class T_DLL_EXPORT CGameObject
{
private:
	u64 m_nMuffinGameObectGUID;
	tbool m_bEnable;
	IComponent* m_pComponents;

	u64 m_nLineTweenIDGen;
	vector<CLineTween*> m_vecSerialLineTween;
	vector<CLineTween*> m_vecParallelLineTween;

	friend class CGameObjectManager;

private:
	void Update();
	void UpdateAnimation();
	CLineTween* CreateLineTween(ELineTweenType a_eType);

public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vLocalPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

	CGameObject();
	virtual ~CGameObject();

	T_INLINE tbool IsEnable() { return this->m_bEnable; }
	T_INLINE void SetEnable(tbool a_bEnable) { this->m_bEnable = a_bEnable; }
	T_INLINE u64 GetGameObjectID() { return this->m_nMuffinGameObectGUID; }

	void SetRotation(glm::vec3 a_vEulerAngle);
	void UpdateRotation(glm::vec3 a_vEulerAngle);

	void SetRotation(glm::quat a_quat);
	void UpdateRotation(glm::quat a_quat);

	glm::vec3 GetEulerAngle();

	CLineTween* CreateSerialLineTween(ELineTweenType a_eType);
	CLineTween* CreateParallelLineTween(ELineTweenType a_eType);
	virtual void LineTweenDone(u64 a_uAnimationID) {};
};


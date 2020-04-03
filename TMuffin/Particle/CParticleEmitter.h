#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "CParticle.h"
#include "Graphics/CGraphicsComponent.h"

class CMaterial;
class CMesh;
class T_DLL_EXPORT CParticleEmitter : public CComponentBase
{
private:
	TLinkedList<CParticle*> m_objFreeList;
	TLinkedList<CParticle*> m_objEmittedList;
	f64 m_fLastEmitTime;
	EParticleMode m_eMode;
	glm::vec3 m_vCameraPos;
	u32 m_nEmittedCount;

protected:
	virtual void Init() override;
	virtual void Update() override;

public:
	friend class CParticleEmitterManager;

	glm::vec3 m_vMinScale;
	glm::vec3 m_vMaxScale;
	glm::vec3 m_vMinAcceleration;
	glm::vec3 m_vMaxAcceleration;
	glm::vec3 m_vMinVelocity;
	glm::vec3 m_vMaxVelocity;
	glm::vec3 m_vMinDeltaPosition;
	glm::vec3 m_vMaxDeltaPosition;
	glm::vec4 m_vMinColor;
	glm::vec4 m_vMaxColor;
	f32 m_fMinLifeTime;
	f32 m_fMaxLifeTime;
	n32 m_nMinEmitCount;
	n32 m_nMaxEmitCount;
	f32 m_fEmitPeriod;
	tbool m_bIsPeriod;
	tstring m_strMeshFile;
	tstring m_strMaterialFile;
	CMaterial* m_pMaterial;
	CMesh* m_pMesh;

	T_SCS
		T_SCP(m_vMinScale, glm::vec3)
		T_SCP(m_vMaxScale, glm::vec3)
		T_SCP(m_vMinAcceleration, glm::vec3)
		T_SCP(m_vMaxAcceleration, glm::vec3)
		T_SCP(m_vMinVelocity, glm::vec3)
		T_SCP(m_vMaxVelocity, glm::vec3)
		T_SCP(m_vMinDeltaPosition, glm::vec3)
		T_SCP(m_vMaxDeltaPosition, glm::vec3)
		T_SCP(m_vMinColor, glm::vec4)
		T_SCP(m_vMaxColor, glm::vec4)
		T_SCP(m_fMinLifeTime, f64)
		T_SCP(m_fMaxLifeTime, f64)
		T_SCP(m_nMinEmitCount, n32)
		T_SCP(m_nMaxEmitCount, n32)
		T_SCP(m_fEmitPeriod, f64)
		T_SCP(m_bIsPeriod, tbool)
		T_SCP(m_strMeshFile, tstring)
		T_SCP(m_strMaterialFile, tstring)
	T_SCE

public:
	CParticleEmitter();
	~CParticleEmitter();

	void EmitParticle();
	void AwakeParticle(CParticle* a_pParticle);

	void SetParticleMode(EParticleMode a_eMode);
	void SetCameraPosition(glm::vec3 a_vPosition);

	void Reset();
};



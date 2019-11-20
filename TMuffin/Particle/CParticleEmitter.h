#pragma once

class T_DLL_EXPORT CParticleEmitter
{
private:
	u64 m_nMuffinEngineGUID;
	TLinkedList<CParticle> m_objFreeList;
	TLinkedList<CParticle> m_objEmittedList;
	f64 m_fLastEmitTime;
	EParticleMode m_eMode;
	glm::vec3 m_vCameraPos;
	u32 m_nEmittedCount;
	
public:
	friend class CParticleEmitterManager;

	tbool m_bEnable;
	glm::vec3 m_vPosition;
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
	CMaterialBase* m_pMaterial;
	CMesh* m_pMesh;

public:
	CParticleEmitter();
	~CParticleEmitter();

	void InitializeEmitter();
	void EmitParticle();
	void AwakeParticle(CParticle* a_pParticle);
	void Update();

	void SetParticleMode(EParticleMode a_eMode);
	void SetCameraPosition(glm::vec3 a_vPosition);

	void Reset();
};




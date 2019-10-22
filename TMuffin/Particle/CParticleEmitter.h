#pragma once

class T_DLL_EXPORT CParticleEmitter
{
#define DEFAULT_EMITTER_PARTICLE_NUM 100

private:
	TLinkedList<CParticle> m_objFreeList;
	TLinkedList<CParticle> m_objEmittedList;
	f32 m_fLastEmitTime;
	f32 m_fLastUpdateTime;
	
public:
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
	n32 m_nShaderID;
	CMesh* m_pMesh;

public:
	CParticleEmitter();
	~CParticleEmitter();

	void InitializeEmitter();
	void EmitParticle();
	void AwakeParticle(CParticle* a_pParticle);
	void Update(f32 a_fFrameTime);
};




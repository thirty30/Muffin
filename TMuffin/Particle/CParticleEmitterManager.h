#pragma once
#include "TMuffinSysInclude.h"

class CParticleEmitter;
class CParticleEmitterManager
{
public:
	hash_map<u64, CParticleEmitter*> m_mapID2Emitter;

public:
	CParticleEmitterManager();
	~CParticleEmitterManager();

	void AddEmitter(CParticleEmitter* a_pComponent);
	void RemoveEmitter(CParticleEmitter* a_pComponent);
	CParticleEmitter* FindEmitter(u64 a_nGUID);
	void Update();
};


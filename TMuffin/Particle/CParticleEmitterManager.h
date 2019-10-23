#pragma once

class CParticleEmitterManager
{
public:
	hash_map<u64, CParticleEmitter*> m_mapID2Emitter;

public:
	CParticleEmitterManager();
	~CParticleEmitterManager();

	CParticleEmitter* CreateEmitter();
	CParticleEmitter* FindEmitterByID(u64 a_nGUID);
	void DeleteEmitter(CParticleEmitter* a_pGameObject);
	void Update();
};



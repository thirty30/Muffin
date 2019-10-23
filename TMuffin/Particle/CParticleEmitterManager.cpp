#include "pch.h"

CParticleEmitterManager::CParticleEmitterManager()
{
	this->m_mapID2Emitter.clear();
}

CParticleEmitterManager::~CParticleEmitterManager()
{
	hash_map<u64, CParticleEmitter*>::const_iterator iter = this->m_mapID2Emitter.begin();
	for (; iter != this->m_mapID2Emitter.end(); iter++)
	{
		delete iter->second;
	}
	this->m_mapID2Emitter.clear();
}

CParticleEmitter* CParticleEmitterManager::CreateEmitter()
{
	u64 nGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_PARTICLE_EMITTER);
	CParticleEmitter* pEmitter = new CParticleEmitter();
	pEmitter->m_nMuffinEngineGUID = nGUID;
	this->m_mapID2Emitter[nGUID] = pEmitter;
	return pEmitter;
}

CParticleEmitter* CParticleEmitterManager::FindEmitterByID(u64 a_nGUID)
{
	hash_map<u64, CParticleEmitter*>::const_iterator iter = this->m_mapID2Emitter.find(a_nGUID);
	if (iter == this->m_mapID2Emitter.end())
	{
		return NULL;
	}
	return iter->second;
}

void CParticleEmitterManager::DeleteEmitter(CParticleEmitter* a_pEmitter)
{
	u64 nGUID = a_pEmitter->m_nMuffinEngineGUID;
	CParticleEmitter* pEmitter = this->FindEmitterByID(nGUID);
	if (pEmitter == NULL)
	{
		return;
	}
	delete pEmitter;
	this->m_mapID2Emitter.erase(nGUID);
}

void CParticleEmitterManager::Update()
{
	hash_map<u64, CParticleEmitter*>::const_iterator iter = this->m_mapID2Emitter.begin();
	for (; iter != this->m_mapID2Emitter.end(); iter++)
	{
		CParticleEmitter* pEmitter = iter->second;
		if (pEmitter != NULL)
		{
			pEmitter->Update();
		}
	}
}

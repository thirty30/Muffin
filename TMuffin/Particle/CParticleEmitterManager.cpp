#include "CParticleEmitterManager.h"
#include "Engine/Engine.h"
#include "CParticleEmitter.h"
#include "CommonDefine.h"
#include "Utility/CGUIDMaker.h"

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

void CParticleEmitterManager::AddEmitter(CParticleEmitter* a_pComponent)
{
	u64 nGUID = a_pComponent->GetGameObject()->GetGameObjectID();
	this->m_mapID2Emitter[nGUID] = a_pComponent;
}

void CParticleEmitterManager::RemoveEmitter(CParticleEmitter* a_pComponent)
{
	u64 nGUID = a_pComponent->GetGameObject()->GetGameObjectID();
	CParticleEmitter* pEmitter = this->FindEmitter(nGUID);
	if (pEmitter == NULL)
	{
		return;
	}
	delete pEmitter;
	this->m_mapID2Emitter.erase(nGUID);
}

CParticleEmitter* CParticleEmitterManager::FindEmitter(u64 a_nGUID)
{
	hash_map<u64, CParticleEmitter*>::const_iterator iter = this->m_mapID2Emitter.find(a_nGUID);
	if (iter == this->m_mapID2Emitter.end())
	{
		return NULL;
	}
	return iter->second;
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

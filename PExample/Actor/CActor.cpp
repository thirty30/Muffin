#include "stdafx.h"

CActor::CActor() : CPhysicsObject(this), CGraphicsObject(this)
{

}

CActor::~CActor()
{

}

//this->pTempParticle = TMuffin_CreateParticleEmitter();
//pTempParticle->m_vPosition = this->m_vPosition;
//pTempParticle->m_vMinScale = glm::vec3(0.5f, 0.5f, 0.5f);
//pTempParticle->m_vMaxScale = glm::vec3(1.5f, 1.5f, 1.5f);
//pTempParticle->m_vMinAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
//pTempParticle->m_vMaxAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
//pTempParticle->m_vMinVelocity = glm::vec3(-10.0f, -10.0f, -10.0f);
//pTempParticle->m_vMaxVelocity = glm::vec3(10.0f, 10.0f, 10.0f);
//pTempParticle->m_vMinDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
//pTempParticle->m_vMaxDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
//pTempParticle->m_vMinColor = glm::vec4(0.9f, 0.39f, 0.13f, 1.0f);
//pTempParticle->m_vMaxColor = glm::vec4(0.9f, 0.129f, 0.058f, 1.0f);
//pTempParticle->m_fMinLifeTime = 1.0f;
//pTempParticle->m_fMaxLifeTime = 2.0f;
//pTempParticle->m_nMinEmitCount = 10;
//pTempParticle->m_nMaxEmitCount = 20;
//pTempParticle->m_fEmitPeriod = 0.5f;
//pTempParticle->m_pMesh = pMeshTriangle;
////pTempParticle->m_nShaderID = nShaderProgramDefaultID;
//pTempParticle->InitializeEmitter();
//this->pTempParticle->m_bEnable = false;
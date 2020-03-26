#include "CParticleEmitter.h"
#include "Engine/Engine.h"

CParticleEmitter::CParticleEmitter()
{
	this->m_fLastEmitTime = 0;
	this->m_eMode = E_PARTICLE_MODE_NORMAL;
	this->m_vCameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_nEmittedCount = 0;

	this->m_vMinScale = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMaxScale = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMinAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMaxAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMinVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMaxVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMinDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMaxDeltaPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMinColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_vMaxColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_fMinLifeTime = 0;
	this->m_fMaxLifeTime = 0;
	this->m_nMinEmitCount = 0;
	this->m_nMaxEmitCount = 0;
	this->m_fEmitPeriod = 0;
	this->m_bIsPeriod = true;
	this->m_pMaterial = NULL;
	this->m_pMesh = NULL;
}

CParticleEmitter::~CParticleEmitter()
{

}

void CParticleEmitter::Init()
{
	f32 fPeriod = this->m_fEmitPeriod <= 0 ? 1.0f : this->m_fEmitPeriod;
	n32 nRatio = (n32)(this->m_fMaxLifeTime / fPeriod) + 1;
	n32 nParticleNum = nRatio * this->m_nMaxEmitCount;
	for (n32 i = 0; i < nParticleNum; i++)
	{
		CParticle* pParticle = new CParticle();
		pParticle->SetEnable(false);
		CGraphicsComponent* pGraphics = pParticle->AddComponent<CGraphicsComponent>();
		pGraphics->InitRenderer(this->m_pMesh, this->m_pMaterial);

		TLinkedNode<CParticle*>* pNode = new TLinkedNode<CParticle*>(pParticle);
		this->m_objFreeList.PushBack(pNode);
	}
}

void CParticleEmitter::EmitParticle()
{
	if (this->m_bIsPeriod == false && this->m_nEmittedCount > 0)
	{
		return;
	}
	n32 nParticleNum = TRandInRange(this->m_nMinEmitCount, this->m_nMaxEmitCount);
	for (n32 i = 0; i < nParticleNum; i++)
	{
		TLinkedNode<CParticle*>* pNode = this->m_objFreeList.PopBack();
		if (pNode == NULL)
		{
			CParticle* pParticle = new CParticle();
			CGraphicsComponent* pGraphics = pParticle->AddComponent<CGraphicsComponent>();
			pGraphics->InitRenderer(this->m_pMesh, this->m_pMaterial);
			pNode = new TLinkedNode<CParticle*>(pParticle);
		}
		this->AwakeParticle(pNode->m_pValue);
		this->m_objEmittedList.PushBack(pNode);
	}
	this->m_nEmittedCount++;
}

void CParticleEmitter::AwakeParticle(CParticle* a_pParticle)
{
	a_pParticle->SetEnable(true);

	a_pParticle->m_fLifeTime = TRandInRange(this->m_fMinLifeTime, this->m_fMaxLifeTime);

	a_pParticle->m_vVelocity.x = TRandInRange(this->m_vMinVelocity.x, this->m_vMaxVelocity.x);
	a_pParticle->m_vVelocity.y = TRandInRange(this->m_vMinVelocity.y, this->m_vMaxVelocity.y);
	a_pParticle->m_vVelocity.z = TRandInRange(this->m_vMinVelocity.z, this->m_vMaxVelocity.z);

	a_pParticle->m_vAcceleration.x = TRandInRange(this->m_vMinAcceleration.x, this->m_vMaxAcceleration.x);
	a_pParticle->m_vAcceleration.y = TRandInRange(this->m_vMinAcceleration.y, this->m_vMaxAcceleration.y);
	a_pParticle->m_vAcceleration.z = TRandInRange(this->m_vMinAcceleration.z, this->m_vMaxAcceleration.z);

	CTransform& rTrans = a_pParticle->GetTransform();
	CTransform& rEmitterTrans = this->GetGameObject()->GetTransform();
	rTrans.m_vPosition.x = rEmitterTrans.m_vPosition.x + TRandInRange(this->m_vMinDeltaPosition.x, this->m_vMaxDeltaPosition.x);
	rTrans.m_vPosition.y = rEmitterTrans.m_vPosition.y + TRandInRange(this->m_vMinDeltaPosition.y, this->m_vMaxDeltaPosition.y);
	rTrans.m_vPosition.z = rEmitterTrans.m_vPosition.z + TRandInRange(this->m_vMinDeltaPosition.z, this->m_vMaxDeltaPosition.z);
	
	rTrans.m_vScale.x = TRandInRange(this->m_vMinScale.x, this->m_vMaxScale.x);
	rTrans.m_vScale.y = TRandInRange(this->m_vMinScale.y, this->m_vMaxScale.y);
	rTrans.m_vScale.z = TRandInRange(this->m_vMinScale.z, this->m_vMaxScale.z);

	glm::vec4 vRGBA;
	vRGBA.r = TRandInRange(this->m_vMinColor.r, this->m_vMaxColor.r);
	vRGBA.g = TRandInRange(this->m_vMinColor.g, this->m_vMaxColor.g);
	vRGBA.b = TRandInRange(this->m_vMinColor.b, this->m_vMaxColor.b);
	vRGBA.a = TRandInRange(this->m_vMinColor.a, this->m_vMaxColor.a);
}

void CParticleEmitter::Update()
{
	f32 fDeltaTime = MUFFIN.GetDeltaFrameTime();
	TLinkedNode<CParticle*>* pNode = this->m_objEmittedList.GetHeadNode();
	while (pNode != NULL)
	{
		CParticle* pCurParticle = pNode->m_pValue;
		CTransform& rTrans = pCurParticle->GetTransform();
		glm::vec3 vDis = pCurParticle->m_vVelocity * fDeltaTime + 0.5f * pCurParticle->m_vAcceleration * fDeltaTime * fDeltaTime;
		rTrans.m_vPosition += vDis;
		pCurParticle->m_vVelocity += pCurParticle->m_vAcceleration * fDeltaTime;
		pCurParticle->m_fLifeTime -= fDeltaTime;

		// Bill Board
		if (this->m_eMode == E_PARTICLE_MODE_BILLBOARD)
		{
			f32 fAngle = glm::atan(rTrans.m_vPosition.x - this->m_vCameraPos.x, rTrans.m_vPosition.z - this->m_vCameraPos.z);
			rTrans.SetRotation(glm::vec3(0.0f, fAngle, 0.0f));
		}

		if (pCurParticle->m_fLifeTime <= 0)
		{
			pCurParticle->SetEnable(false);
			TLinkedNode<CParticle*>* pRemoveNode = pNode;
			pNode = pNode->m_pNext;
			this->m_objEmittedList.RemoveNode(pRemoveNode);
			this->m_objFreeList.PushBack(pRemoveNode);
			continue;
		}
		pNode = pNode->m_pNext;
	}

	if (MUFFIN.GetNowFrameTime() - this->m_fLastEmitTime < this->m_fEmitPeriod)
	{
		return;
	}
	this->m_fLastEmitTime = MUFFIN.GetNowFrameTime();
	this->EmitParticle();
}

void CParticleEmitter::SetParticleMode(EParticleMode a_eMode)
{
	this->m_eMode = a_eMode;
}

void CParticleEmitter::SetCameraPosition(glm::vec3 a_vPosition)
{
	this->m_vCameraPos = a_vPosition;
}

void CParticleEmitter::Reset()
{
	this->m_fLastEmitTime = 0;
	this->m_nEmittedCount = 0;
}


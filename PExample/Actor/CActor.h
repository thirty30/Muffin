#pragma once

class CActor : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
public:
	CActor();
	~CActor();
};

class CCubeActor : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
private:
	CParticleEmitter* pTempParticle;
public:
	CCubeActor();
	~CCubeActor();
	virtual void OnCollision(SCollisionInfo& a_rCollision);
};


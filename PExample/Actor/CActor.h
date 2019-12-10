#pragma once

class CActor : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
public:
	n32 m_nActorID;

	CActor();
	~CActor();

	virtual void Update() {}
};


class CZone : public CGameObject, public CPhysicsObject
{
public:
	CZone();
	~CZone();

	virtual void OnCollision(SCollisionInfo& a_rCollision);
};
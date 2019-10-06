#pragma once

class CObjectPhysics : public CSingleton<CObjectPhysics>
{
private:
	f32 m_gravity;

public:
	CObjectPhysics();
	~CObjectPhysics();

	void PhysicsObjects();
};
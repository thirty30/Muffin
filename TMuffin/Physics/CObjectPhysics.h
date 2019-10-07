#pragma once

class CObjectPhysics : public CSingleton<CObjectPhysics>
{
private:
	glm::vec3 m_vGravity;

public:
	CObjectPhysics();
	~CObjectPhysics();

	void PhysicsObjects(f32 a_fDeltaTime);
};
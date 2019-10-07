#pragma once

class T_DLL_EXPORT CGameObject : public CMuffinObject
{
public:	
	CMeshRenderer m_pMeshRenderer;
	CPhysicsAttribute m_pPhysicsAttribute;

public:
	CGameObject(u64 a_uGUID) : CMuffinObject(a_uGUID)
	{
	}

	~CGameObject()
	{
	}

	u64 GetGUID() { return this->m_nGUID; };
	tbool InitMeshRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID);

	inline tbool NeedRendering() { return this->m_pMeshRenderer.m_bIsRendering; }
	inline tbool NeedPhysics() { return this->m_pPhysicsAttribute.m_bIsPhysics; }
};




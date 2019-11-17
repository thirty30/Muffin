#pragma once

struct SDrawVertex
{
	f32 x, y, z, w;
	f32 r, g, b, a;
	f32 nx, ny, nz, nw;
	f32 u0, v0, u1, v1;
	SDrawVertex()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;

		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;

		this->nx = 0;
		this->ny = 0;
		this->nz = 0;
		this->nw = 1;

		this->u0 = 1;
		this->v0 = 1;
		this->u1 = 1;
		this->v1 = 1;
	}
};

class CMeshDrawInfo
{
public:
	u32 m_nVAOID;

	u32 m_nVertexGLBufferID;
	n32 m_nVertexCount;
	SDrawVertex* m_pVertices;

	u32 m_nTriangleIndexGLBufferID;
	n32 m_nTriangleCount;
	n32 m_nTriangleIndexCount;
	u32* m_pTriangleIndices;

public:
	CMeshDrawInfo()
	{
		this->m_nVAOID = 0;

		this->m_nVertexGLBufferID = 0;
		this->m_nVertexCount = 0;
		this->m_pVertices = NULL;

		this->m_nTriangleIndexGLBufferID = 0;
		this->m_nTriangleCount = 0;
		this->m_nTriangleIndexCount = 0;
		this->m_pTriangleIndices = NULL;
	}

	~CMeshDrawInfo() 
	{
		if (this->m_pVertices != NULL)
		{
			delete this->m_pVertices;
		}
		if (this->m_pTriangleIndices != NULL)
		{
			delete this->m_pTriangleIndices;
		}
	}
};

class T_DLL_EXPORT CGraphicsObject
{
private:
	u64 m_nMuffinGraphicsObectGUID;
	CGameObject* m_pGameObject;
	friend class CGraphicsRenderer;

public:
	CMeshDrawInfo* m_pMeshDrawInfo;
	CMaterialBase* m_pMaterial;
	n32 m_nRenderMode;

public:
	CGraphicsObject(CGameObject* a_pGameObject);
	virtual ~CGraphicsObject();

	tbool InitRenderer(const CMesh* a_pMesh, CMaterialBase* a_pMaterial);
	void SetRenderMode(ERenderMode a_eMode);

	virtual void LightPass();
	virtual void MaterialPass();
};





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

	u32 m_nTriangelIndexGLBufferID;
	n32 m_nTriangelCount;
	n32 m_nTriangelIndexCount;
	u32* m_pTriangelIndices;

public:
	CMeshDrawInfo()
	{
		this->m_nVAOID = 0;

		this->m_nVertexGLBufferID = 0;
		this->m_nVertexCount = 0;
		this->m_pVertices = NULL;

		this->m_nTriangelIndexGLBufferID = 0;
		this->m_nTriangelCount = 0;
		this->m_nTriangelIndexCount = 0;
		this->m_pTriangelIndices = NULL;
	}

	~CMeshDrawInfo() 
	{
		if (this->m_pVertices != NULL)
		{
			delete this->m_pVertices;
		}
		if (this->m_pTriangelIndices != NULL)
		{
			delete this->m_pTriangelIndices;
		}
	}
};

class T_DLL_EXPORT CMeshRenderer : public CComponent
{
public:
	n32 m_nShaderProgramID;
	CMeshDrawInfo* m_pMeshDrawInfo;
	n32 m_nRenderMode;
	glm::vec3 m_vRGB;

public:
	CMeshRenderer() 
	{
		this->m_eComponentType = E_COMPONENT_MESH_RENDER;
		this->m_nShaderProgramID = 0;
		this->m_pMeshDrawInfo = NULL;
		this->m_nRenderMode = GL_FILL;
		this->m_vRGB = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	~CMeshRenderer(){}

	tbool InitRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID);
	void SetRenderMode(ERenderMode a_eMode);
};





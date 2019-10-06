#pragma once

struct SDrawVertex
{
	float X, Y, Z;
	float R, G, B;
	SDrawVertex()
	{
		this->X = 0;
		this->Y = 0;
		this->Z = 0;

		this->R = 1.0f;
		this->G = 1.0f;
		this->B = 1.0f;
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

class T_DLL_EXPORT CMeshRenderer
{
public:
	n32 m_nShaderProgramID;
	CMeshDrawInfo* m_pMeshDrawInfo;
	n32 m_nRenderMode;

public:
	CMeshRenderer() 
	{
		this->m_nShaderProgramID = 0;
		this->m_pMeshDrawInfo = NULL;
		this->m_nRenderMode = GL_FILL;
	}
	~CMeshRenderer(){}

	tbool InitRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID);
	void SetRenderMode(ERenderMode a_eMode);
};





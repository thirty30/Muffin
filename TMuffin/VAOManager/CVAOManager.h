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

		this->R = 0;
		this->G = 0;
		this->B = 0;
	}
};

class T_DLL_EXPORT CModelDrawInfo
{
public:
	CModelDrawInfo() 
	{
		this->m_nCustomID = 0;
		this->m_pMesh = NULL;

		this->m_nVAOID = 0;

		this->m_nVertexGLBufferID = 0;
		this->m_nVertexCount = 0;
		this->m_pVertices = NULL;

		this->m_nTriangelIndexGLBufferID = 0;
		this->m_nTriangelCount = 0;
		this->m_nTriangelIndexCount = 0;
		this->m_pTriangelIndices = NULL;
	};
	~CModelDrawInfo() {};

public:
	n32 m_nCustomID;
	CMesh* m_pMesh;

	u32 m_nVAOID;

	u32 m_nVertexGLBufferID;
	n32 m_nVertexCount;
	SDrawVertex* m_pVertices;

	u32 m_nTriangelIndexGLBufferID;
	n32 m_nTriangelCount;
	n32 m_nTriangelIndexCount;
	u32* m_pTriangelIndices;
};


class T_DLL_EXPORT CVAOManager
{
private:
	hash_map<n32, CModelDrawInfo*> m_mapCustomID2Info;

public:
	//a_nCustomID is a custom id by user to identify the model, recommend to be a enum
	tbool LoadModel(n32 a_nCustomID, tstring a_strPath, n32 a_nShaderProgramID);
	CModelDrawInfo* FindModel(n32 a_nID);
};

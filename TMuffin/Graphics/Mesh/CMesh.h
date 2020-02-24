#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"

struct SBoneInfo
{
	n32 boneID[BONE_NUM];
	f32 boneWeight[BONE_NUM];

	SBoneInfo()
	{
		TMemzero(this->boneID, sizeof(n32) * BONE_NUM);
		TMemzero(this->boneWeight, sizeof(f32) * BONE_NUM);
	}

	void AddBone(n32 a_nBoneID, f32 a_fWeight) 
	{
		for (n32 i = 0; i < BONE_NUM; i++)
		{
			if (boneWeight[i] == 0.0f)
			{
				this->boneID[i] = a_nBoneID;
				this->boneWeight[i] = a_fWeight;
				break;
			}
		}
	}
};

struct SBoneDetail
{
	tstring boneName;
	n32 boneID;
	glm::mat4 BoneOffset;
	glm::mat4 FinalTransformation;
	glm::mat4 ObjectBoneTransformation;
};

struct SMeshVertex
{
	f32 x, y, z;
	f32 nx, ny, nz;
	f32 r, g, b, a;
	f32 u0, v0, u1, v1;

	f32 tx, ty, tz;
	f32 bx, by, bz;
	n32 boneID[BONE_NUM];
	f32 boneWeight[BONE_NUM];

	SMeshVertex()
	{
		this->x = 0; this->y = 0; this->z = 0;
		this->r = 1; this->g = 1; this->b = 1; this->a = 1;
		this->nx = 0; this->ny = 0; this->nz = 0;
		this->u0 = 0; this->v0 = 0; this->u1 = 0; this->v1 = 0;
		this->tx = 0, this->ty = 0, this->tz = 0;
		this->bx = 0, this->by = 0, this->bz = 0;
		TMemzero(this->boneID, sizeof(n32) * BONE_NUM);
		TMemzero(this->boneWeight, sizeof(f32) * BONE_NUM);
	}
};

struct SMeshTriangle
{
	u32 Vertex1, Vertex2, Vertex3;
	SMeshTriangle()
	{
		this->Vertex1 = 0;
		this->Vertex2 = 0;
		this->Vertex3 = 0;
	}
};

class T_DLL_EXPORT CMesh
{
public:
	n32 m_nVertexCount;
	SMeshVertex* m_pVertices;	//store the vertices

	n32 m_nTriangleCount;
	SMeshTriangle* m_pTriangles;	//store the triangels

	hash_map<tstring, SBoneDetail*> m_mapName2Bone;
	glm::mat4 m_matInverseTransformation;

public:
	CMesh();
	~CMesh();
};


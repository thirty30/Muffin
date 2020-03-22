#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "CAssetObject.h"

struct SBoneInfo
{
	n32 boneID[BONE_NUM];
	f32 boneWeight[BONE_NUM];

	SBoneInfo();
	T_INLINE void AddBone(n32 a_nBoneID, f32 a_fWeight);
};

struct SBoneDetail
{
	n32 boneID;
	tstring boneName;
	glm::mat4 BoneOffset;
	glm::mat4 FinalTransformation;
	glm::mat4 ObjectBoneTransformation;
};

struct SMeshVertex
{
	f32 x, y, z, w;
	f32 r, g, b, a;
	f32 nx, ny, nz, nw;
	f32 u0, v0, u1, v1;
	f32 tx, ty, tz, tw;
	f32 bx, by, bz, bw;
	n32 boneID[BONE_NUM];
	f32 boneWeight[BONE_NUM];

	SMeshVertex()
	{
		this->x = 0; this->y = 0; this->z = 0; this->w = 1;
		this->r = 1; this->g = 1; this->b = 1; this->a = 1;
		this->nx = 0; this->ny = 0; this->nz = 0; this->nw = 1;
		this->u0 = 1; this->v0 = 1; this->u1 = 1; this->v1 = 1;
		this->tx = 0, this->ty = 0, this->tz = 0, this->tw = 1;
		this->bx = 0, this->by = 0, this->bz = 0, this->bw = 1;
		TMemzero(this->boneID, sizeof(n32) * BONE_NUM);
		TMemzero(this->boneWeight, sizeof(f32) * BONE_NUM);
	}
};

class T_DLL_EXPORT CMesh : public CAssetObject
{
public:
	GLuint m_nVAOID;
	GLuint m_nVertexBufferID;
	GLuint m_nTriangleBufferID;

public:
	n32 m_nVertexCount;
	SMeshVertex* m_pVertices;	//store the vertices

	n32 m_nTriangleCount;		//triangle num
	n32 m_nTriangleIndexCount;	//triangle vertice num
	u32* m_pTriangleIndices;	//store the triangels

	glm::mat4 m_matInverseTransformation;
	hash_map<tstring, SBoneDetail*> m_mapName2Bone;
	
public:
	CMesh();
	~CMesh();

	T_INLINE GLint GetVAOID() { return this->m_nVAOID; }
	T_INLINE GLint GetVertexBufferID() { return this->m_nVertexBufferID; }
	T_INLINE GLint GetTriangleBufferID() { return this->m_nTriangleBufferID; }

protected:
	virtual tbool LoadToMemory(const tcchar* a_strFileName) override;
	virtual tbool InitAfterLoad() override;
	
	friend class CAssetsLoader;
	friend class CAssetsWorker;
	friend class CAssetsPool;
};


#include "CMesh.h"
#include "CAssetObject.h"
#include "Utility/Utility.h"

SBoneInfo::SBoneInfo()
{
	TMemzero(this->boneID, sizeof(n32) * BONE_NUM);
	TMemzero(this->boneWeight, sizeof(f32) * BONE_NUM);
}

void SBoneInfo::AddBone(n32 a_nBoneID, f32 a_fWeight)
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

CMesh::CMesh() : CAssetObject(EAT_MESH)
{
	this->m_nVertexCount = 0;
	this->m_pVertices = NULL;
	this->m_nTriangleCount = 0;
	this->m_pTriangleIndices = NULL;
	this->m_mapName2Bone.clear();
}

CMesh::~CMesh()
{
	if (this->m_pVertices != NULL)
	{
		delete []this->m_pVertices;
	}
	if (this->m_pTriangleIndices != NULL)
	{
		delete []this->m_pTriangleIndices;
	}

	hash_map<tstring, SBoneDetail*>::const_iterator iter = this->m_mapName2Bone.begin();
	for (; iter != m_mapName2Bone.end(); iter++)
	{
		delete iter->second;
	}
	this->m_mapName2Bone.clear();
}

tbool CMesh::LoadToMemory(const tcchar* a_strFileName)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(a_strFileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GlobalScale |
		aiProcess_GenNormals |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph);

	// If the import failed, report it
	if (pScene == NULL)
	{
		return false;
	}

	if (pScene->HasMeshes() == false)
	{
		return false;
	}

	this->m_matInverseTransformation = AIMatrixToGLMMatrix(pScene->mRootNode->mTransformation);
	this->m_matInverseTransformation = glm::inverse(this->m_matInverseTransformation);

	aiMesh* pMesh = pScene->mMeshes[0];
	SBoneInfo* pBoneArray = NULL;
	if (pMesh->HasBones() == true)
	{
		pBoneArray = new SBoneInfo[pMesh->mNumVertices];
		for (n32 i = 0; i < pMesh->mNumBones; i++)
		{
			tstring strBoneName(pMesh->mBones[i]->mName.C_Str());

			SBoneDetail* pDetail = new SBoneDetail();
			pDetail->boneName = strBoneName;
			pDetail->boneID = i;
			pDetail->BoneOffset = AIMatrixToGLMMatrix(pMesh->mBones[i]->mOffsetMatrix);
			this->m_mapName2Bone[strBoneName] = pDetail;

			n32 nNumWeights = pMesh->mBones[i]->mNumWeights;
			for (n32 j = 0; j < nNumWeights; j++)
			{
				aiVertexWeight* pAIWeight = pMesh->mBones[i]->mWeights;
				n32 nVertexID = pAIWeight[j].mVertexId;
				f32 fVertexWeight = pAIWeight[j].mWeight;

				pBoneArray[nVertexID].AddBone(i, fVertexWeight);
			}
		}
	}

	this->m_nVertexCount = pMesh->mNumVertices;
	this->m_nTriangleCount = pMesh->mNumFaces;

	this->m_pVertices = new SMeshVertex[this->m_nVertexCount];
	for (n32 i = 0; i < this->m_nVertexCount; i++)
	{
		this->m_pVertices[i].x = pMesh->mVertices[i].x;
		this->m_pVertices[i].y = pMesh->mVertices[i].y;
		this->m_pVertices[i].z = pMesh->mVertices[i].z;

		if (pMesh->HasVertexColors(0) == true)
		{
			this->m_pVertices[i].r = pMesh->mColors[0][i].r;
			this->m_pVertices[i].g = pMesh->mColors[0][i].g;
			this->m_pVertices[i].b = pMesh->mColors[0][i].b;
			this->m_pVertices[i].a = pMesh->mColors[0][i].a;
		}

		if (pMesh->HasNormals() == true)
		{
			this->m_pVertices[i].nx = pMesh->mNormals[i].x;
			this->m_pVertices[i].ny = pMesh->mNormals[i].y;
			this->m_pVertices[i].nz = pMesh->mNormals[i].z;
		}

		if (pMesh->HasTextureCoords(0) == true)
		{
			this->m_pVertices[i].u0 = pMesh->mTextureCoords[0][i].x;
			this->m_pVertices[i].v0 = pMesh->mTextureCoords[0][i].y;
		}

		if (pMesh->HasTangentsAndBitangents() == true)
		{
			this->m_pVertices[i].tx = pMesh->mTangents[i].x;
			this->m_pVertices[i].ty = pMesh->mTangents[i].y;
			this->m_pVertices[i].tz = pMesh->mTangents[i].z;

			this->m_pVertices[i].bx = pMesh->mBitangents[i].x;
			this->m_pVertices[i].by = pMesh->mBitangents[i].y;
			this->m_pVertices[i].bz = pMesh->mBitangents[i].z;
		}

		if (pBoneArray != NULL)
		{
			this->m_pVertices[i].boneID[0] = pBoneArray[i].boneID[0];
			this->m_pVertices[i].boneID[1] = pBoneArray[i].boneID[1];
			this->m_pVertices[i].boneID[2] = pBoneArray[i].boneID[2];
			this->m_pVertices[i].boneID[3] = pBoneArray[i].boneID[3];

			this->m_pVertices[i].boneWeight[0] = pBoneArray[i].boneWeight[0];
			this->m_pVertices[i].boneWeight[1] = pBoneArray[i].boneWeight[1];
			this->m_pVertices[i].boneWeight[2] = pBoneArray[i].boneWeight[2];
			this->m_pVertices[i].boneWeight[3] = pBoneArray[i].boneWeight[3];
		}
	}

	this->m_nTriangleIndexCount = this->m_nTriangleCount * 3;
	this->m_pTriangleIndices = new u32[this->m_nTriangleIndexCount];
	for (n32 i = 0; i < this->m_nTriangleCount; i++)
	{
		this->m_pTriangleIndices[(i * 3) + 0] = pMesh->mFaces[i].mIndices[0];
		this->m_pTriangleIndices[(i * 3) + 1] = pMesh->mFaces[i].mIndices[1];
		this->m_pTriangleIndices[(i * 3) + 2] = pMesh->mFaces[i].mIndices[2];
	}

	if (pBoneArray != NULL)
	{
		delete[] pBoneArray;
	}
	return true;
}

tbool CMesh::InitAfterLoad()
{
	glGenVertexArrays(1, &(this->m_nVAOID));	// Ask OpenGL for a new buffer ID
	glBindVertexArray(this->m_nVAOID);	// "Bind" this buffer: "make this the 'current' VAO buffer

	// Copy the vertices into the video card
	glGenBuffers(1, &(this->m_nVertexBufferID));
	glBindBuffer(GL_ARRAY_BUFFER, this->m_nVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SMeshVertex) * this->m_nVertexCount, (GLvoid*)this->m_pVertices, GL_STATIC_DRAW);

	// Copy the index buffer into the video card
	glGenBuffers(1, &(this->m_nTriangleBufferID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_nTriangleBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * this->m_nTriangleIndexCount, (GLvoid*)this->m_pTriangleIndices, GL_STATIC_DRAW);

	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}


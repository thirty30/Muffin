#include "CResourceLoader.h"
#include "Graphics/Mesh/CMesh.h"
#include "Utility/Utility.h"

tbool CResourceLoader::LoadModelFromPly(const tcchar* a_strFileName, CMesh* a_pMesh)
{
	if (a_pMesh == NULL)
	{
		return false;
	}

	ifstream objFile(a_strFileName);
	if (objFile.is_open() != true)
	{
		cout << "can't open the file" << endl;
		return false;
	}

	tstring strContent;
	while (objFile >> strContent)
	{
		if (strContent == "vertex")
		{
			objFile >> a_pMesh->m_nVertexCount;
			continue;
		}
		if (strContent == "face")
		{
			objFile >> a_pMesh->m_nTriangleCount;
			continue;
		}
		if (strContent == "end_header")
		{
			//read all vertices
			a_pMesh->m_pVertices = new SMeshVertex[a_pMesh->m_nVertexCount];
			for (u32 i = 0; i < a_pMesh->m_nVertexCount; i++)
			{
				SMeshVertex& rTemp = a_pMesh->m_pVertices[i];
				objFile >> rTemp.x >> rTemp.y >> rTemp.z;
				objFile >> rTemp.nx >> rTemp.ny >> rTemp.nz;
			}

			//read all triangels
			a_pMesh->m_pTriangles = new SMeshTriangle[a_pMesh->m_nTriangleCount];
			for (u32 i = 0; i < a_pMesh->m_nTriangleCount; i++)
			{
				SMeshTriangle& rTemp = a_pMesh->m_pTriangles[i];
				int nDiscard = 0;
				objFile >> nDiscard >> rTemp.Vertex1 >> rTemp.Vertex2 >> rTemp.Vertex3;
			}
		}
	}

	objFile.close();
	return true;
}

tbool CResourceLoader::LoadModelFromPlyUV(const tcchar* a_strFileName, CMesh* a_pMesh)
{
	if (a_pMesh == NULL)
	{
		return false;
	}

	ifstream objFile(a_strFileName);
	if (objFile.is_open() != true)
	{
		cout << "can't open the file" << endl;
		return false;
	}

	tstring strContent;
	while (objFile >> strContent)
	{
		if (strContent == "vertex")
		{
			objFile >> a_pMesh->m_nVertexCount;
			continue;
		}
		if (strContent == "face")
		{
			objFile >> a_pMesh->m_nTriangleCount;
			continue;
		}
		if (strContent == "end_header")
		{
			//read all vertices
			a_pMesh->m_pVertices = new SMeshVertex[a_pMesh->m_nVertexCount];
			for (u32 i = 0; i < a_pMesh->m_nVertexCount; i++)
			{
				SMeshVertex& rTemp = a_pMesh->m_pVertices[i];
				objFile >> rTemp.x >> rTemp.y >> rTemp.z;
				objFile >> rTemp.nx >> rTemp.ny >> rTemp.nz;
				objFile >> rTemp.u0 >> rTemp.v0;
				rTemp.u1 = 1.0f;
				rTemp.v1 = 1.0f;
			}

			//read all triangels
			a_pMesh->m_pTriangles = new SMeshTriangle[a_pMesh->m_nTriangleCount];
			for (u32 i = 0; i < a_pMesh->m_nTriangleCount; i++)
			{
				SMeshTriangle& rTemp = a_pMesh->m_pTriangles[i];
				int nDiscard = 0;
				objFile >> nDiscard >> rTemp.Vertex1 >> rTemp.Vertex2 >> rTemp.Vertex3;
			}
		}
	}

	objFile.close();
	return true;
}

tbool CResourceLoader::LoadMesh(const tcchar* a_strFileName, CMesh* a_pMesh)
{
	if (a_pMesh == NULL)
	{
		return false;
	}
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
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

	a_pMesh->m_matInverseTransformation = AIMatrixToGLMMatrix(pScene->mRootNode->mTransformation);
	a_pMesh->m_matInverseTransformation = glm::inverse(a_pMesh->m_matInverseTransformation);

	//f64 factor = 0.0f;
	//pScene->mMetaData->Get("UnitScaleFactor", factor);
	aiMesh* pMesh = pScene->mMeshes[0];

	SBoneInfo* pBoneArray = NULL;
	if (pMesh->HasBones() == true)
	{
		pBoneArray = new SBoneInfo[pMesh->mNumVertices];
		for (n32 i = 0; i < pMesh->mNumBones; i++)
		{
			tstring strBoneName(pMesh->mBones[i]->mName.C_Str());

			//auto iter = a_pMesh->m_mapName2Bone.find(strBoneName);
			//if (iter != a_pMesh->m_mapName2Bone.end())
			//{
			//	cout << " ####################" << endl;
			//}

			SBoneDetail* pDetail = new SBoneDetail();
			pDetail->boneName = strBoneName;
			pDetail->boneID = i;
			pDetail->BoneOffset = AIMatrixToGLMMatrix(pMesh->mBones[i]->mOffsetMatrix);
			a_pMesh->m_mapName2Bone[strBoneName] = pDetail;



			//cout << "Bone: " << pMesh->mBones[i]->mName.C_Str() << endl;
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
	 
	a_pMesh->m_nVertexCount = pMesh->mNumVertices;
	a_pMesh->m_nTriangleCount = pMesh->mNumFaces;

	a_pMesh->m_pVertices = new SMeshVertex[a_pMesh->m_nVertexCount];
	for (n32 i = 0; i < a_pMesh->m_nVertexCount; i++)
	{
		a_pMesh->m_pVertices[i].x = pMesh->mVertices[i].x;
		a_pMesh->m_pVertices[i].y = pMesh->mVertices[i].y;
		a_pMesh->m_pVertices[i].z = pMesh->mVertices[i].z;

		if (pMesh->HasVertexColors(0) == true)
		{
			a_pMesh->m_pVertices[i].r = pMesh->mColors[0][i].r;
			a_pMesh->m_pVertices[i].g = pMesh->mColors[0][i].g;
			a_pMesh->m_pVertices[i].b = pMesh->mColors[0][i].b;
			a_pMesh->m_pVertices[i].a = pMesh->mColors[0][i].a;
		}
		
		if (pMesh->HasNormals() == true)
		{
			a_pMesh->m_pVertices[i].nx = pMesh->mNormals[i].x;
			a_pMesh->m_pVertices[i].ny = pMesh->mNormals[i].y;
			a_pMesh->m_pVertices[i].nz = pMesh->mNormals[i].z;
		}

		if (pMesh->HasTextureCoords(0) == true)
		{
			a_pMesh->m_pVertices[i].u0 = pMesh->mTextureCoords[0][i].x;
			a_pMesh->m_pVertices[i].v0 = pMesh->mTextureCoords[0][i].y;
			a_pMesh->m_pVertices[i].u1 = 1.0f;
			a_pMesh->m_pVertices[i].v1 = 1.0f;
		}

		if (pMesh->HasTangentsAndBitangents() == true)
		{
			a_pMesh->m_pVertices[i].tx = pMesh->mTangents[i].x;
			a_pMesh->m_pVertices[i].ty = pMesh->mTangents[i].y;
			a_pMesh->m_pVertices[i].tz = pMesh->mTangents[i].z;

			a_pMesh->m_pVertices[i].bx = pMesh->mBitangents[i].x;
			a_pMesh->m_pVertices[i].by = pMesh->mBitangents[i].y;
			a_pMesh->m_pVertices[i].bz = pMesh->mBitangents[i].z;
		}

		if (pBoneArray != NULL)
		{
			a_pMesh->m_pVertices[i].boneID[0] = pBoneArray[i].boneID[0];
			a_pMesh->m_pVertices[i].boneID[1] = pBoneArray[i].boneID[1];
			a_pMesh->m_pVertices[i].boneID[2] = pBoneArray[i].boneID[2];
			a_pMesh->m_pVertices[i].boneID[3] = pBoneArray[i].boneID[3];

			a_pMesh->m_pVertices[i].boneWeight[0] = pBoneArray[i].boneWeight[0];
			a_pMesh->m_pVertices[i].boneWeight[1] = pBoneArray[i].boneWeight[1];
			a_pMesh->m_pVertices[i].boneWeight[2] = pBoneArray[i].boneWeight[2];
			a_pMesh->m_pVertices[i].boneWeight[3] = pBoneArray[i].boneWeight[3];
		}
	}

	if (pBoneArray != NULL)
	{
		delete[] pBoneArray;
	}
	

	a_pMesh->m_pTriangles = new SMeshTriangle[a_pMesh->m_nTriangleCount];
	for (n32 i = 0; i < a_pMesh->m_nTriangleCount; i++)
	{
		a_pMesh->m_pTriangles[i].Vertex1 = pMesh->mFaces[i].mIndices[0];
		a_pMesh->m_pTriangles[i].Vertex2 = pMesh->mFaces[i].mIndices[1];
		a_pMesh->m_pTriangles[i].Vertex3 = pMesh->mFaces[i].mIndices[2];
	}
	return true;
}

#include "pch.h"

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

tbool CResourceLoader::LoadTextureFromBMP(const tcchar* a_strFileName, CTexture* a_pTexture)
{

	return  true;
}

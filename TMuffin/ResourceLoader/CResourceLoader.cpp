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
			objFile >> a_pMesh->m_nTriangelCount;
			continue;
		}
		if (strContent == "end_header")
		{
			//read all vertices
			a_pMesh->m_pVertices = new SMeshVertex[a_pMesh->m_nVertexCount];
			for (u32 i = 0; i < a_pMesh->m_nVertexCount; i++)
			{
				SMeshVertex& rTemp = a_pMesh->m_pVertices[i];
				objFile >> rTemp.X >> rTemp.Y >> rTemp.Z;
				objFile >> rTemp.NX >> rTemp.NY >> rTemp.NZ;
			}

			//read all triangels
			a_pMesh->m_pTriangels = new SMeshTriangel[a_pMesh->m_nTriangelCount];
			for (u32 i = 0; i < a_pMesh->m_nTriangelCount; i++)
			{
				SMeshTriangel& rTemp = a_pMesh->m_pTriangels[i];
				int nDiscard = 0;
				objFile >> nDiscard >> rTemp.Vertex1 >> rTemp.Vertex2 >> rTemp.Vertex3;
			}
		}
	}

	objFile.close();
	return true;
}

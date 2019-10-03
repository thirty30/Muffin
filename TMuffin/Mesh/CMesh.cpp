#include "pch.h"

CMesh::CMesh()
{
	this->m_nVertexCount = 0;
	this->m_pVertices = NULL;
	this->m_nTriangelCount = 0;
	this->m_pTriangels = NULL;
}

CMesh::~CMesh()
{
	if (this->m_pVertices != NULL)
	{
		delete []this->m_pVertices;
	}
	if (this->m_pTriangels != NULL)
	{
		delete []this->m_pTriangels;
	}
}

tbool CMesh::LoadPlyModel(tstring a_strFileName)
{
	ifstream objFile(a_strFileName.c_str());
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
			objFile >> this->m_nVertexCount;
			continue;
		}
		if (strContent == "face")
		{
			objFile >> this->m_nTriangelCount;
			continue;
		}
		if (strContent == "end_header")
		{
			//read all vertices
			this->m_pVertices = new SMeshVertex[this->m_nVertexCount];
			for (u32 i = 0; i < this->m_nVertexCount; i++)
			{
				SMeshVertex& rTemp = this->m_pVertices[i];
				objFile >> rTemp.X >> rTemp.Y >> rTemp.Z;
			}

			//read all triangels
			this->m_pTriangels = new SMeshTriangel[this->m_nTriangelCount];
			for (u32 i = 0; i < this->m_nTriangelCount; i++)
			{
				SMeshTriangel& rTemp = this->m_pTriangels[i];
				int nDiscard = 0;
				objFile >> nDiscard >> rTemp.Vertex1 >> rTemp.Vertex2 >> rTemp.Vertex3;
			}
		}
	}

	objFile.close();
	return true;
}

const SMeshVertex* CMesh::GetVertex(n32 a_nIndex)
{
	if (a_nIndex < 0 || a_nIndex >= this->m_nVertexCount)
	{
		return NULL;
	}
	return &this->m_pVertices[a_nIndex];
}

const SMeshTriangel* CMesh::GetTriangel(n32 a_nIndex)
{
	if (a_nIndex < 0 || a_nIndex >= this->m_nTriangelCount)
	{
		return NULL;
	}
	return &this->m_pTriangels[a_nIndex];
}

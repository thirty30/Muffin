#include "CMesh.h"

CMesh::CMesh()
{
	this->m_nVertexCount = 0;
	this->m_pVertices = NULL;
	this->m_nTriangleCount = 0;
	this->m_pTriangles = NULL;
	this->m_mapName2Bone.clear();
}

CMesh::~CMesh()
{
	if (this->m_pVertices != NULL)
	{
		delete []this->m_pVertices;
	}
	if (this->m_pTriangles != NULL)
	{
		delete []this->m_pTriangles;
	}

	for (auto iter : this->m_mapName2Bone)
	{
		delete iter.second;
	}
	this->m_mapName2Bone.clear();
}

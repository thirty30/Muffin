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

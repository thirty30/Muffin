#include "pch.h"

tbool CVAOManager::LoadModel(n32 a_nCustomID, tstring a_strPath, n32 a_nShaderProgramID)
{
	if (this->FindModel(a_nCustomID) != NULL)
	{
		return false;
	}
	CMesh* pMesh = new CMesh();
	if (pMesh->LoadPlyModel(a_strPath) == false)
	{
		delete pMesh;
		return false;
	}
	
	CModelDrawInfo* pDrawInfo = new CModelDrawInfo();
	pDrawInfo->m_nCustomID = a_nCustomID;
	pDrawInfo->m_pMesh = pMesh;
	pDrawInfo->m_nVertexCount = pMesh->GetVertexCount();
	pDrawInfo->m_pVertices = new SDrawVertex[pDrawInfo->m_nVertexCount];
	TMemzero(pDrawInfo->m_pVertices, pDrawInfo->m_nVertexCount);
	for (n32 i = 0; i < pDrawInfo->m_nVertexCount; i++)
	{
		const SMeshVertex* pVertex = pMesh->GetVertex(i);
		if (pVertex == NULL)
		{
			delete pMesh;
			delete pDrawInfo;
			return false;
		}
		pDrawInfo->m_pVertices[i].X = pVertex->X;
		pDrawInfo->m_pVertices[i].Y = pVertex->Y;
		pDrawInfo->m_pVertices[i].Z = pVertex->Z;

		pDrawInfo->m_pVertices[i].R = 1.0f;
		pDrawInfo->m_pVertices[i].G = 1.0f;
		pDrawInfo->m_pVertices[i].B = 1.0f;
	}

	pDrawInfo->m_nTriangelCount = pMesh->GetTriangelCount();
	pDrawInfo ->m_nTriangelIndexCount = pDrawInfo->m_nTriangelCount * 3;
	pDrawInfo->m_pTriangelIndices = new u32[pDrawInfo->m_nTriangelIndexCount];
	TMemzero(pDrawInfo->m_pTriangelIndices, pDrawInfo->m_nTriangelIndexCount);
	for (n32 i = 0; i < pDrawInfo->m_nTriangelCount; i++)
	{
		const SMeshTriangel* pTriangel = pMesh->GetTriangel(i);
		if (pTriangel == NULL)
		{
			delete pMesh;
			delete pDrawInfo;
			return false;
		}
		pDrawInfo->m_pTriangelIndices[(i * 3) + 0] = pTriangel->Vertex1;
		pDrawInfo->m_pTriangelIndices[(i * 3) + 1] = pTriangel->Vertex2;
		pDrawInfo->m_pTriangelIndices[(i * 3) + 2] = pTriangel->Vertex3;
	}
	this->m_mapCustomID2Info[a_nCustomID] = pDrawInfo;

	
	glGenVertexArrays(1, &(pDrawInfo->m_nVAOID));	// Ask OpenGL for a new buffer ID
	glBindVertexArray(pDrawInfo->m_nVAOID);	// "Bind" this buffer: "make this the 'current' VAO buffer

	// Copy the vertices into the video card
	glGenBuffers(1, &(pDrawInfo->m_nVertexGLBufferID));
	glBindBuffer(GL_ARRAY_BUFFER, pDrawInfo->m_nVertexGLBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SDrawVertex) * pDrawInfo->m_nVertexCount, (GLvoid*)pDrawInfo->m_pVertices, GL_STATIC_DRAW);

	// Copy the index buffer into the video card
	glGenBuffers(1, &(pDrawInfo->m_nTriangelIndexGLBufferID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pDrawInfo->m_nTriangelIndexGLBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * pDrawInfo->m_nTriangelIndexCount, (GLvoid*)pDrawInfo->m_pTriangelIndices, GL_STATIC_DRAW);

	// Set the vertex attributes.
	GLint nPositionLocation = glGetAttribLocation(a_nShaderProgramID, "vPosition");
	GLint nColorLocation = glGetAttribLocation(a_nShaderProgramID, "vColor");

	// Set the vertex attributes for this shader
	glEnableVertexAttribArray(nPositionLocation);
	glVertexAttribPointer(nPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(SDrawVertex), (void*)(offsetof(SDrawVertex, X)));

	glEnableVertexAttribArray(nColorLocation);
	glVertexAttribPointer(nColorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(SDrawVertex), (void*)(offsetof(SDrawVertex, R)));

	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(nPositionLocation);
	glDisableVertexAttribArray(nColorLocation);

	return true;
}

CModelDrawInfo* CVAOManager::FindModel(n32 a_nID)
{
	hash_map<n32, CModelDrawInfo*>::iterator iter = this->m_mapCustomID2Info.find(a_nID);
	if (iter == this->m_mapCustomID2Info.end())
	{
		return NULL;
	}
	return iter->second;
}

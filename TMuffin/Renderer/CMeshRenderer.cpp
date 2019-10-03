#include "pch.h"

tbool CMeshRenderer::InitRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID)
{
	this->m_pMeshDrawInfo = new CMeshDrawInfo();
	this->m_pMeshDrawInfo->m_nVertexCount = a_pMesh->m_nVertexCount;
	this->m_pMeshDrawInfo->m_pVertices = new SDrawVertex[this->m_pMeshDrawInfo->m_nVertexCount];
	TMemzero(this->m_pMeshDrawInfo->m_pVertices, this->m_pMeshDrawInfo->m_nVertexCount);
	for (n32 i = 0; i < this->m_pMeshDrawInfo->m_nVertexCount; i++)
	{
		const SMeshVertex* pVertex = &a_pMesh->m_pVertices[i];
		if (pVertex == NULL)
		{
			delete this->m_pMeshDrawInfo;
			return false;
		}
		this->m_pMeshDrawInfo->m_pVertices[i].X = pVertex->X;
		this->m_pMeshDrawInfo->m_pVertices[i].Y = pVertex->Y;
		this->m_pMeshDrawInfo->m_pVertices[i].Z = pVertex->Z;
	}

	this->m_pMeshDrawInfo->m_nTriangelCount = a_pMesh->m_nTriangelCount;
	this->m_pMeshDrawInfo->m_nTriangelIndexCount = a_pMesh->m_nTriangelCount * 3;
	this->m_pMeshDrawInfo->m_pTriangelIndices = new u32[this->m_pMeshDrawInfo->m_nTriangelIndexCount];
	TMemzero(this->m_pMeshDrawInfo->m_pTriangelIndices, this->m_pMeshDrawInfo->m_nTriangelIndexCount);
	for (n32 i = 0; i < this->m_pMeshDrawInfo->m_nTriangelCount; i++)
	{
		const SMeshTriangel* pTriangel = &a_pMesh->m_pTriangels[i];
		if (pTriangel == NULL)
		{
			delete this->m_pMeshDrawInfo;
			return false;
		}
		this->m_pMeshDrawInfo->m_pTriangelIndices[(i * 3) + 0] = pTriangel->Vertex1;
		this->m_pMeshDrawInfo->m_pTriangelIndices[(i * 3) + 1] = pTriangel->Vertex2;
		this->m_pMeshDrawInfo->m_pTriangelIndices[(i * 3) + 2] = pTriangel->Vertex3;
	}

	this->m_nShaderProgramID = a_nShaderProgramID;
	glGenVertexArrays(1, &(this->m_pMeshDrawInfo->m_nVAOID));	// Ask OpenGL for a new buffer ID
	glBindVertexArray(this->m_pMeshDrawInfo->m_nVAOID);	// "Bind" this buffer: "make this the 'current' VAO buffer

	// Copy the vertices into the video card
	glGenBuffers(1, &(this->m_pMeshDrawInfo->m_nVertexGLBufferID));
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pMeshDrawInfo->m_nVertexGLBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SDrawVertex) * this->m_pMeshDrawInfo->m_nVertexCount, (GLvoid*)this->m_pMeshDrawInfo->m_pVertices, GL_STATIC_DRAW);

	// Copy the index buffer into the video card
	glGenBuffers(1, &(this->m_pMeshDrawInfo->m_nTriangelIndexGLBufferID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_pMeshDrawInfo->m_nTriangelIndexGLBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * this->m_pMeshDrawInfo->m_nTriangelIndexCount, (GLvoid*)this->m_pMeshDrawInfo->m_pTriangelIndices, GL_STATIC_DRAW);

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

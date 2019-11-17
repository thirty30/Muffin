#include "pch.h"

CGraphicsObject::CGraphicsObject(CGameObject* a_pGameObject)
{
	this->m_nMuffinGraphicsObectGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_GRAPHICS_OBJECT);
	this->m_pGameObject = a_pGameObject;
	this->m_pMeshDrawInfo = NULL;
	this->m_nRenderMode = GL_FILL;
	this->m_pMaterial = NULL;

	MUFFIN.GetGraphicsRenderer()->AddObject(this);
}

CGraphicsObject::~CGraphicsObject()
{
	if (this->m_pMeshDrawInfo != NULL)
	{
		delete this->m_pMeshDrawInfo;
		this->m_pMeshDrawInfo = NULL;
	}
}

tbool CGraphicsObject::InitRenderer(const CMesh* a_pMesh, CMaterialBase* a_pMaterial)
{
	if (a_pMesh == NULL || a_pMaterial == NULL)
	{
		return false;
	}
	this->m_pMaterial = a_pMaterial;
	this->m_pMeshDrawInfo = new CMeshDrawInfo();
	this->m_pMeshDrawInfo->m_nVertexCount = a_pMesh->m_nVertexCount;
	this->m_pMeshDrawInfo->m_pVertices = new SDrawVertex[this->m_pMeshDrawInfo->m_nVertexCount];
	for (n32 i = 0; i < this->m_pMeshDrawInfo->m_nVertexCount; i++)
	{
		const SMeshVertex* pVertex = &a_pMesh->m_pVertices[i];
		if (pVertex == NULL)
		{
			delete this->m_pMeshDrawInfo;
			return false;
		}
		this->m_pMeshDrawInfo->m_pVertices[i].x = pVertex->x;
		this->m_pMeshDrawInfo->m_pVertices[i].y = pVertex->y;
		this->m_pMeshDrawInfo->m_pVertices[i].z = pVertex->z;
		this->m_pMeshDrawInfo->m_pVertices[i].w = 1.0f;

		this->m_pMeshDrawInfo->m_pVertices[i].r = 1.0f;
		this->m_pMeshDrawInfo->m_pVertices[i].g = 1.0f;
		this->m_pMeshDrawInfo->m_pVertices[i].b = 1.0f;
		this->m_pMeshDrawInfo->m_pVertices[i].a = 1.0f;

		this->m_pMeshDrawInfo->m_pVertices[i].nx = pVertex->nx;
		this->m_pMeshDrawInfo->m_pVertices[i].ny = pVertex->ny;
		this->m_pMeshDrawInfo->m_pVertices[i].nz = pVertex->nz;
		this->m_pMeshDrawInfo->m_pVertices[i].nw = 1.0f;

		this->m_pMeshDrawInfo->m_pVertices[i].u0 = pVertex->u0;
		this->m_pMeshDrawInfo->m_pVertices[i].v0 = pVertex->v0;
		this->m_pMeshDrawInfo->m_pVertices[i].u1 = pVertex->u1;
		this->m_pMeshDrawInfo->m_pVertices[i].v1 = pVertex->v1;
	}

	this->m_pMeshDrawInfo->m_nTriangleCount = a_pMesh->m_nTriangleCount;
	this->m_pMeshDrawInfo->m_nTriangleIndexCount = a_pMesh->m_nTriangleCount * 3;
	this->m_pMeshDrawInfo->m_pTriangleIndices = new u32[this->m_pMeshDrawInfo->m_nTriangleIndexCount];
	TMemzero(this->m_pMeshDrawInfo->m_pTriangleIndices, this->m_pMeshDrawInfo->m_nTriangleIndexCount);
	for (n32 i = 0; i < this->m_pMeshDrawInfo->m_nTriangleCount; i++)
	{
		const SMeshTriangle* pTriangel = &a_pMesh->m_pTriangles[i];
		if (pTriangel == NULL)
		{
			delete this->m_pMeshDrawInfo;
			return false;
		}
		this->m_pMeshDrawInfo->m_pTriangleIndices[(i * 3) + 0] = pTriangel->Vertex1;
		this->m_pMeshDrawInfo->m_pTriangleIndices[(i * 3) + 1] = pTriangel->Vertex2;
		this->m_pMeshDrawInfo->m_pTriangleIndices[(i * 3) + 2] = pTriangel->Vertex3;
	}

	n32 nShaderProgramID = this->m_pMaterial->GetShaderProgramID();
	glGenVertexArrays(1, &(this->m_pMeshDrawInfo->m_nVAOID));	// Ask OpenGL for a new buffer ID
	glBindVertexArray(this->m_pMeshDrawInfo->m_nVAOID);	// "Bind" this buffer: "make this the 'current' VAO buffer

	// Copy the vertices into the video card
	glGenBuffers(1, &(this->m_pMeshDrawInfo->m_nVertexGLBufferID));
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pMeshDrawInfo->m_nVertexGLBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SDrawVertex) * this->m_pMeshDrawInfo->m_nVertexCount, (GLvoid*)this->m_pMeshDrawInfo->m_pVertices, GL_STATIC_DRAW);

	// Copy the index buffer into the video card
	glGenBuffers(1, &(this->m_pMeshDrawInfo->m_nTriangleIndexGLBufferID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_pMeshDrawInfo->m_nTriangleIndexGLBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * this->m_pMeshDrawInfo->m_nTriangleIndexCount, (GLvoid*)this->m_pMeshDrawInfo->m_pTriangleIndices, GL_STATIC_DRAW);

	// Set the vertex attributes.
	GLint nPositionLocation = glGetAttribLocation(nShaderProgramID, "vPosition");
	GLint nColorLocation = glGetAttribLocation(nShaderProgramID, "vColor");
	GLint nNormalLocation = glGetAttribLocation(nShaderProgramID, "vNormal");
	GLint nUVLocation = glGetAttribLocation(nShaderProgramID, "vUVx2");

	// Set the vertex attributes for this shader
	glEnableVertexAttribArray(nPositionLocation);
	glVertexAttribPointer(nPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SDrawVertex), (void*)(offsetof(SDrawVertex, x)));

	glEnableVertexAttribArray(nColorLocation);
	glVertexAttribPointer(nColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SDrawVertex), (void*)(offsetof(SDrawVertex, r)));

	glEnableVertexAttribArray(nNormalLocation);
	glVertexAttribPointer(nNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SDrawVertex), (void*)(offsetof(SDrawVertex, nx)));

	glEnableVertexAttribArray(nUVLocation);
	glVertexAttribPointer(nUVLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SDrawVertex), (void*)(offsetof(SDrawVertex, u0)));

	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(nPositionLocation);
	glDisableVertexAttribArray(nColorLocation);

	return true;
}

void CGraphicsObject::SetRenderMode(ERenderMode a_eMode)
{
	if (a_eMode == E_RENDER_MODE_POINT)
	{
		this->m_nRenderMode = GL_POINT;
	}
	else if (a_eMode == E_RENDER_MODE_LINE)
	{
		this->m_nRenderMode = GL_LINE;
	}
	else
	{
		this->m_nRenderMode = GL_FILL;
	}
}

void CGraphicsObject::LightPass()
{
	if (this->m_pMaterial == NULL)
	{
		return;
	}
	MUFFIN.GetLightMgr()->RenderLights(this->m_pMaterial->GetShaderProgramID());
}

void CGraphicsObject::MaterialPass()
{
	if (this->m_pMaterial == NULL)
	{
		return;
	}
	this->m_pMaterial->RenderMaterial();
}

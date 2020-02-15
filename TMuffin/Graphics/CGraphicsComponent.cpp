#include "CGraphicsComponent.h"
#include "CGraphicsWorld.h"
#include "Material/CMaterial.h"
#include "Mesh/CMesh.h"
#include "Engine/Engine.h"
#include "Utility/CGUIDMaker.h"
#include "Light/CLightManager.h"
#include "ResourceLoader/CResourceLoader.h"

CGraphicsComponent::CGraphicsComponent()
{
	this->m_nRenderMode = GL_FILL;
	this->m_pDrawMesh = NULL;
	this->m_pMaterial = NULL;
}

CGraphicsComponent::~CGraphicsComponent()
{
	if (this->m_pDrawMesh != NULL)
	{
		delete this->m_pDrawMesh;
		this->m_pDrawMesh = NULL;
	}
	if (this->m_pMaterial != NULL)
	{
		delete this->m_pMaterial;
		this->m_pMaterial = NULL;
	}
	MUFFIN.GetGraphicsWorld()->RemoveGraphicsObject(this);
}

void CGraphicsComponent::Init()
{
	if (this->m_pDrawMesh == NULL && this->m_pMaterial == NULL)
	{
		CMesh* pMesh = new CMesh();
		CResourceLoader::LoadMesh(this->MeshFile.c_str(), pMesh);
		CMaterial* pMat = new CMaterial();
		pMat->Init(this->MaterialFile);
		this->InitRenderer(pMesh, pMat);
		delete pMesh;
	}
	MUFFIN.GetGraphicsWorld()->AddGraphicsObject(this);
}

tbool CGraphicsComponent::InitRenderer(const CMesh* a_pMesh, CMaterial* a_pMaterial)
{
	if (a_pMesh == NULL || a_pMaterial == NULL)
	{
		return false;
	}
	this->m_pMaterial = a_pMaterial;
	n32 nShaderProgramID = this->m_pMaterial->GetShaderID();

	this->m_pDrawMesh = new SDrawMesh();
	this->m_pDrawMesh->m_nVertexCount = a_pMesh->m_nVertexCount;
	this->m_pDrawMesh->m_pVertices = new SDrawVertex[this->m_pDrawMesh->m_nVertexCount];
	for (n32 i = 0; i < this->m_pDrawMesh->m_nVertexCount; i++)
	{
		const SMeshVertex* pVertex = &a_pMesh->m_pVertices[i];
		if (pVertex == NULL)
		{
			delete this->m_pDrawMesh;
			return false;
		}
		this->m_pDrawMesh->m_pVertices[i].x = pVertex->x;
		this->m_pDrawMesh->m_pVertices[i].y = pVertex->y;
		this->m_pDrawMesh->m_pVertices[i].z = pVertex->z;
		this->m_pDrawMesh->m_pVertices[i].w = 1.0f;

		this->m_pDrawMesh->m_pVertices[i].r = pVertex->r;
		this->m_pDrawMesh->m_pVertices[i].g = pVertex->g;
		this->m_pDrawMesh->m_pVertices[i].b = pVertex->b;
		this->m_pDrawMesh->m_pVertices[i].a = pVertex->a;

		this->m_pDrawMesh->m_pVertices[i].nx = pVertex->nx;
		this->m_pDrawMesh->m_pVertices[i].ny = pVertex->ny;
		this->m_pDrawMesh->m_pVertices[i].nz = pVertex->nz;
		this->m_pDrawMesh->m_pVertices[i].nw = 1.0f;

		this->m_pDrawMesh->m_pVertices[i].u0 = pVertex->u0;
		this->m_pDrawMesh->m_pVertices[i].v0 = pVertex->v0;
		this->m_pDrawMesh->m_pVertices[i].u1 = pVertex->u1;
		this->m_pDrawMesh->m_pVertices[i].v1 = pVertex->v1;
	}

	this->m_pDrawMesh->m_nTriangleCount = a_pMesh->m_nTriangleCount;
	this->m_pDrawMesh->m_nTriangleIndexCount = a_pMesh->m_nTriangleCount * 3;
	this->m_pDrawMesh->m_pTriangleIndices = new u32[this->m_pDrawMesh->m_nTriangleIndexCount];
	TMemzero(this->m_pDrawMesh->m_pTriangleIndices, this->m_pDrawMesh->m_nTriangleIndexCount * sizeof(u32));

	for (n32 i = 0; i < this->m_pDrawMesh->m_nTriangleCount; i++)
	{
		const SMeshTriangle* pTriangel = &a_pMesh->m_pTriangles[i];
		if (pTriangel == NULL)
		{
			delete this->m_pDrawMesh;
			return false;
		}
		this->m_pDrawMesh->m_pTriangleIndices[(i * 3) + 0] = pTriangel->Vertex1;
		this->m_pDrawMesh->m_pTriangleIndices[(i * 3) + 1] = pTriangel->Vertex2;
		this->m_pDrawMesh->m_pTriangleIndices[(i * 3) + 2] = pTriangel->Vertex3;
	}

	
	glGenVertexArrays(1, &(this->m_pDrawMesh->m_nVAOID));	// Ask OpenGL for a new buffer ID
	glBindVertexArray(this->m_pDrawMesh->m_nVAOID);	// "Bind" this buffer: "make this the 'current' VAO buffer

	// Copy the vertices into the video card
	glGenBuffers(1, &(this->m_pDrawMesh->m_nVertexGLBufferID));
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pDrawMesh->m_nVertexGLBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SDrawVertex) * this->m_pDrawMesh->m_nVertexCount, (GLvoid*)this->m_pDrawMesh->m_pVertices, GL_STATIC_DRAW);

	// Copy the index buffer into the video card
	glGenBuffers(1, &(this->m_pDrawMesh->m_nTriangleIndexGLBufferID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_pDrawMesh->m_nTriangleIndexGLBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * this->m_pDrawMesh->m_nTriangleIndexCount, (GLvoid*)this->m_pDrawMesh->m_pTriangleIndices, GL_STATIC_DRAW);

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

void CGraphicsComponent::SetRenderMode(ERenderMode a_eMode)
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

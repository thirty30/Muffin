#include "pch.h"

CSkyBox::CSkyBox()
{
	this->m_nShaderID = -1;
	this->m_pMeshDrawInfo = NULL;
	this->m_nTextureID = -1;
	this->m_nULSampler = -1;
}

CSkyBox::~CSkyBox()
{

}

void CSkyBox::InitMesh(const CMesh* a_pMesh)
{
	this->m_pMeshDrawInfo = new CMeshDrawInfo();
	this->m_pMeshDrawInfo->m_nVertexCount = a_pMesh->m_nVertexCount;
	this->m_pMeshDrawInfo->m_pVertices = new SDrawVertex[this->m_pMeshDrawInfo->m_nVertexCount];
	for (n32 i = 0; i < this->m_pMeshDrawInfo->m_nVertexCount; i++)
	{
		const SMeshVertex* pVertex = &a_pMesh->m_pVertices[i];
		if (pVertex == NULL)
		{
			delete this->m_pMeshDrawInfo;
			return;
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
			return;
		}
		this->m_pMeshDrawInfo->m_pTriangleIndices[(i * 3) + 0] = pTriangel->Vertex1;
		this->m_pMeshDrawInfo->m_pTriangleIndices[(i * 3) + 1] = pTriangel->Vertex2;
		this->m_pMeshDrawInfo->m_pTriangleIndices[(i * 3) + 2] = pTriangel->Vertex3;
	}

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
	GLint nPositionLocation = glGetAttribLocation(this->m_nShaderID, "vPosition");
	GLint nColorLocation = glGetAttribLocation(this->m_nShaderID, "vColor");
	GLint nNormalLocation = glGetAttribLocation(this->m_nShaderID, "vNormal");
	GLint nUVLocation = glGetAttribLocation(this->m_nShaderID, "vUVx2");

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
}

tbool CSkyBox::LoadImage(GLenum a_eValue, const tcchar* a_strFileName)
{
	FREE_IMAGE_FORMAT eFormat = FreeImage_GetFileType(a_strFileName);
	FIBITMAP* pBitMap = NULL;
	BYTE* pBytes = NULL;

	if (eFormat == FIF_UNKNOWN)
	{
		return false;
	}

	if (FreeImage_FIFSupportsReading(eFormat) == true)
	{
		pBitMap = FreeImage_Load(eFormat, a_strFileName);
	}

	if (pBitMap == NULL)
	{
		return false;
	}

	pBytes = FreeImage_GetBits(pBitMap);

	n32 nWidth = FreeImage_GetWidth(pBitMap);
	n32 nHeight = FreeImage_GetHeight(pBitMap);

	if (pBytes == NULL || nWidth == 0 || nHeight == 0)
	{
		return false;
	}

	if (a_eValue == GL_TEXTURE_CUBE_MAP_POSITIVE_X)
	{
		glTexStorage2D(GL_TEXTURE_CUBE_MAP, 10, GL_RGBA8, nWidth, nHeight);
	}
	if (eFormat == FIF_PNG)
	{
		glTexSubImage2D(a_eValue, 0, 0, 0, nWidth, nHeight, GL_BGRA, GL_UNSIGNED_BYTE, pBytes);
	}
	else
	{
		glTexSubImage2D(a_eValue, 0, 0, 0, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, pBytes);
	}

	FreeImage_Unload(pBitMap);
	return true;
}

tbool CSkyBox::Init(const CMesh* a_pMesh, n32 a_nShaderID, const tcchar* a_strXTexture, const tcchar* a_strNegXTexture, const tcchar* a_strYTexture, const tcchar* a_strNegYTexture, const tcchar* a_strZTexture, const tcchar* a_strNegZTexture)
{
	this->m_nShaderID = a_nShaderID;
	this->InitMesh(a_pMesh);

	glGenTextures(1, &this->m_nTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_nTextureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	this->LoadImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X, a_strXTexture);
	this->LoadImage(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, a_strNegXTexture);
	this->LoadImage(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, a_strYTexture);
	this->LoadImage(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, a_strNegYTexture);
	this->LoadImage(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, a_strZTexture);
	this->LoadImage(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, a_strNegZTexture);

	this->m_nULSampler = glGetUniformLocation(this->m_nShaderID, "un_Sampler");
	this->m_vScale = glm::vec3(10000.0f, 10000.0f, 10000.0f);

	return true;
}

T_INLINE void CSkyBox::Render()
{
	glCullFace(GL_FRONT_AND_BACK);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_nTextureID);
	glUniform1i(this->m_nULSampler, 0);
}

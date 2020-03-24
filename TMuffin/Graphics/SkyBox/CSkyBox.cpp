#include "CSkyBox.h"
#include "AssetsLoader/AssetObject/CMesh.h"
#include "Graphics/CGraphicsComponent.h"
#include "AssetsLoader/CAssetsLoader.h"

CSkyBox::CSkyBox()
{
	this->m_pMesh = NULL;
	this->m_nTextureID = -1;
	this->m_nULSampler = -1;
	this->m_vScale = glm::vec3(10000.0f, 10000.0f, 10000.0f);
}

CSkyBox::~CSkyBox()
{
	if (this->m_pMesh != NULL)
	{
		delete this->m_pMesh;
		this->m_pMesh = NULL;
	}
}

void CSkyBox::InitMesh(const tcchar* a_strMeshFile)
{
	this->m_pMesh = CAssetsLoader::Load<CMesh>(a_strMeshFile);

	glBindVertexArray(this->m_pMesh->GetVAOID());
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pMesh->GetVertexBufferID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_pMesh->GetTriangleBufferID());

	// Set the vertex attributes.
	n32 nShaderID = this->m_ShaderProgram.GetShaderID();

	// Set the vertex attributes for this shader
	GLint nPositionLocation = glGetAttribLocation(nShaderID, "vPosition");
	glEnableVertexAttribArray(nPositionLocation);
	glVertexAttribPointer(nPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, x)));

	GLint nNormalLocation = glGetAttribLocation(nShaderID, "vNormal");
	glEnableVertexAttribArray(nNormalLocation);
	glVertexAttribPointer(nNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, nx)));

	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(nNormalLocation);
	glDisableVertexAttribArray(nPositionLocation);
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

tbool CSkyBox::Init(const tcchar* a_strMeshFile, const tcchar* a_strVertexShader, const tcchar* a_strFragmentShader, const tcchar* a_strXTexture, const tcchar* a_strNegXTexture, const tcchar* a_strYTexture, const tcchar* a_strNegYTexture, const tcchar* a_strZTexture, const tcchar* a_strNegZTexture)
{
	this->m_ShaderProgram.GetShader(E_SHADER_TYPE_VERTEX)->LoadShaderToMemory(a_strVertexShader);
	this->m_ShaderProgram.GetShader(E_SHADER_TYPE_VERTEX)->InitShader();
	this->m_ShaderProgram.GetShader(E_SHADER_TYPE_FRAGMENT)->LoadShaderToMemory(a_strFragmentShader);
	this->m_ShaderProgram.GetShader(E_SHADER_TYPE_FRAGMENT)->InitShader();
	this->m_ShaderProgram.InitShaderProgram();

	this->InitMesh(a_strMeshFile);

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

	this->m_nULSampler = glGetUniformLocation(this->m_ShaderProgram.GetShaderID(), "un_Sampler");

	return true;
}

T_INLINE void CSkyBox::Render()
{
	glCullFace(GL_FRONT_AND_BACK);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_nTextureID);
	glUniform1i(this->m_nULSampler, 0);
}

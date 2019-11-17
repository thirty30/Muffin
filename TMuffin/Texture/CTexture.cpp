#include "pch.h"

CTexture::CTexture()
{
	this->m_nWidth = 0;
	this->m_nHeight = 0;
	this->m_nTextureID = 0;
}

CTexture::~CTexture()
{
	if (this->m_nTextureID != 0)
	{
		glDeleteTextures(1, &this->m_nTextureID);
	}
}

tbool CTexture::LoadTexture(const tcchar* a_strFileName)
{
	FREE_IMAGE_FORMAT eFormat = FreeImage_GetFileType(a_strFileName);

	//pointer to the image, once loaded
	FIBITMAP* pBitMap = NULL;

	//pointer to the image data
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
		

	//retrieve the image data
	pBytes = FreeImage_GetBits(pBitMap);

	//get the image width and height
	this->m_nWidth = FreeImage_GetWidth(pBitMap);
	this->m_nHeight = FreeImage_GetHeight(pBitMap);

	//if this somehow one of these failed (they shouldn't), return failure
	if (pBytes == NULL || this->m_nWidth == 0 || this->m_nHeight == 0)
	{
		return false;
	}


	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &this->m_nTextureID);

	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, this->m_nTextureID);

	//GLint nOldGLUnpackAligment = 0;
	//glGetIntegerv(GL_UNPACK_ALIGNMENT, &nOldGLUnpackAligment);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//store the texture data for OpenGL use
	if (eFormat == FIF_PNG)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_nWidth, this->m_nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBytes);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_nWidth, this->m_nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pBytes);
	}
	//glPixelStorei(GL_UNPACK_ALIGNMENT, nOldGLUnpackAligment);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Free FreeImage's copy of the data
	FreeImage_Unload(pBitMap);

	//return success
	return true;
}

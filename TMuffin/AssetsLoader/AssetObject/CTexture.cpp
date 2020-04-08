#include "CTexture.h"

CTexture::CTexture() : CAssetObject(EAT_TEXTURE)
{
	this->m_nTextureID = 0;

	this->m_nWidth = 0;
	this->m_nHeight = 0;
	this->m_pImageData = NULL;
}

CTexture::~CTexture()
{
	if (this->m_nTextureID != 0)
	{
		glDeleteTextures(1, &this->m_nTextureID);
	}
	if (this->m_pImageData != NULL)
	{
		delete this->m_pImageData;
	}
	this->m_pImageData = NULL;
}

tbool CTexture::LoadToMemory(const tcchar* a_strFileName)
{
	FREE_IMAGE_FORMAT eFormat = FreeImage_GetFileType(a_strFileName);
	if (eFormat == FIF_UNKNOWN)
	{
		return false;
	}

	if (FreeImage_FIFSupportsReading(eFormat) == false)
	{
		return false;
	}

	//pointer to the image, once loaded
	FIBITMAP* pBitMap = FreeImage_Load(eFormat, a_strFileName);
	if (pBitMap == NULL)
	{
		return false;
	}

	//retrieve the image data
	BYTE* pBytes = FreeImage_GetBits(pBitMap);
	if (pBytes == NULL)
	{
		return false;
	}

	//get the image width and height
	this->m_nWidth = FreeImage_GetWidth(pBitMap);
	this->m_nHeight = FreeImage_GetHeight(pBitMap);
	if (this->m_nWidth == 0 || this->m_nHeight == 0)
	{
		return false;
	}
	this->m_nPixelCount = FreeImage_GetBPP(pBitMap);
	n32 nTotalSize = this->m_nWidth * this->m_nHeight * (this->m_nPixelCount / 8);
	this->m_nTotalSize = nTotalSize;

	this->m_pImageData = new u8[nTotalSize];
	TMemzero(this->m_pImageData, nTotalSize);
	TMemcpy(this->m_pImageData, nTotalSize, pBytes, nTotalSize);
	FreeImage_Unload(pBitMap);
	return true;
}

tbool CTexture::InitAfterLoad()
{
	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &this->m_nTextureID);

	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, this->m_nTextureID);

	//store the texture data for OpenGL use
	if (this->m_nPixelCount == 32)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_nWidth, this->m_nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->m_pImageData);
	}
	else if (this->m_nPixelCount == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_nWidth, this->m_nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_pImageData);
	}
	else
	{
		return false;
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return true;
}

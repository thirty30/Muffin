#pragma once

class T_DLL_EXPORT CTexture
{
private:
	u32 m_nWidth;
	u32 m_nHeight;
	GLuint m_nTextureID;

public:
	CTexture();
	~CTexture();

	tbool LoadTexture(const tcchar* a_strFileName);
	T_INLINE GLuint GetTextureID() { return this->m_nTextureID; }
};


#pragma once
#include "TMuffinSysInclude.h"
#include "CAssetObject.h"

class T_DLL_EXPORT CTexture : public CAssetObject
{
private:
	GLuint m_nTextureID;

public:
	u32 m_nWidth;
	u32 m_nHeight;
	n32 m_nPixelCount;
	n32 m_nTotalSize;
	u8* m_pImageData;

public:
	CTexture();
	~CTexture();

	T_INLINE GLuint GetTextureID() { return this->m_nTextureID; }

protected:
	virtual tbool LoadToMemory(const tcchar* a_strFileName) override;
	virtual tbool InitAfterLoad() override;

	friend class CMaterial;
};


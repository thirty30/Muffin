#pragma once

class T_DLL_EXPORT CSkyBox : public CGameObject
{
private:
	n32 m_nShaderID;
	CMeshDrawInfo* m_pMeshDrawInfo;
	GLuint m_nTextureID;
	GLuint m_nULSampler;

	friend class CGraphicsRenderer;

private:
	void InitMesh(const CMesh* a_pMesh);
	tbool LoadImage(GLenum a_eValue, const tcchar* a_strFileName);
	T_INLINE void Render();

public:
	CSkyBox();
	~CSkyBox();

	tbool Init(const CMesh* a_pMesh, n32 a_nShaderID, 
		const tcchar* a_strXTexture, const tcchar* a_strNegXTexture,
		const tcchar* a_strYTexture, const tcchar* a_strNegYTexture,
		const tcchar* a_strZTexture, const tcchar* a_strNegZTexture
	);
};



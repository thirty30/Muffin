#pragma once
#include "TMuffinSysInclude.h"
#include "GameObject/CGameObject.h"
#include "AssetsLoader/AssetObject/CShader.h"

class CMesh;
class T_DLL_EXPORT CSkyBox
{
private:
	CShaderProgram m_ShaderProgram;

private:
	CMesh* m_pMesh;
	GLuint m_nTextureID;
	GLuint m_nULSampler;
	glm::vec3 m_vScale;

	friend class CGraphicsWorld;

private:
	void InitMesh(const tcchar* a_strMeshFile);
	tbool LoadImage(GLenum a_eValue, const tcchar* a_strFileName);
	T_INLINE void Render();

public:
	CSkyBox();
	~CSkyBox();

	tbool Init(const tcchar* a_strMeshFile,
		const tcchar* a_strVertexShader, const tcchar* a_strFragmentShader,
		const tcchar* a_strXTexture, const tcchar* a_strNegXTexture,
		const tcchar* a_strYTexture, const tcchar* a_strNegYTexture,
		const tcchar* a_strZTexture, const tcchar* a_strNegZTexture
	);
	n32 GetShaderID() { return this->m_ShaderProgram.GetShaderID(); }
};



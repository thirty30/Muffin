#pragma once
#include "TMuffinSysInclude.h"
#include "GameObject/CGameObject.h"
#include "ShaderHelper/CShaderHelper.h"

class CMeshDrawInfo;
class CMesh;
class T_DLL_EXPORT CSkyBox : public CGameObject
{
private:
	CShaderProgram m_Shader;
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

	tbool Init(const CMesh* a_pMesh,
		const tcchar* a_strVertexShader, const tcchar* a_strFragmentShader,
		const tcchar* a_strXTexture, const tcchar* a_strNegXTexture,
		const tcchar* a_strYTexture, const tcchar* a_strNegYTexture,
		const tcchar* a_strZTexture, const tcchar* a_strNegZTexture
	);
	n32 GetShaderID() { return this->m_Shader.GetShaderID(); }
};



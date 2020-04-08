#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "Component/CComponentBase.h"

class CGameObject;
class CMesh;
class CMaterial;
class T_DLL_EXPORT CGraphicsComponent : public CComponentBase
{
private:
	n32 m_nRenderMode;
	CMesh* m_pMesh;
	CMaterial* m_pMaterial;
	friend class CGraphicsWorld;

protected:
	virtual void Init() override;

public:
	tstring m_strMeshFile;
	tstring m_strMaterialFile;
	T_SCS
		T_SCP(m_strMeshFile, tstring)
		T_SCP(m_strMaterialFile, tstring)
	T_SCE

public:
	CGraphicsComponent();
	~CGraphicsComponent();

	T_INLINE void SetRenderMode(ERenderMode a_eMode);

	T_INLINE void SetMesh(CMesh* a_pMesh) { this->m_pMesh = a_pMesh; }
	T_INLINE CMesh* GetMesh() { return this->m_pMesh; }

	T_INLINE void SetMaterial(CMaterial* a_pMaterial) { this->m_pMaterial = a_pMaterial; }
	T_INLINE CMaterial* GetMaterial() { return this->m_pMaterial; }

	void BindMesh();
	void ReBindVertices();
};




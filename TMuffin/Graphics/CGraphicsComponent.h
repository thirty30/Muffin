#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "GraphicsDefine.h"
#include "Component/CComponentBase.h"

class CGameObject;
class CMesh;
class CMaterial;
class T_DLL_EXPORT CGraphicsComponent : public CComponentBase
{
private:
	n32 m_nRenderMode;
	SDrawMesh* m_pDrawMesh;
	CMaterial* m_pMaterial;
	friend class CGraphicsWorld;

protected:
	virtual void Init() override;
	
public:
	CGraphicsComponent();
	~CGraphicsComponent();

	tbool InitRenderer(const CMesh* a_pMesh, CMaterial* a_pMaterial);
	T_INLINE void SetRenderMode(ERenderMode a_eMode);
	T_INLINE CMaterial* GetMaterial() { return this->m_pMaterial; }
};




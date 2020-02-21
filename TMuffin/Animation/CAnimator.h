#pragma once
#include "TMuffinSysInclude.h"
#include "Component/CComponentBase.h"

class CMesh;
class CAnimation;
class T_DLL_EXPORT CAnimator : public CComponentBase
{
private:
	vector<tstring> m_strFileName;
	hash_map<tstring, CAnimation*> m_mapName2Animation;
	CAnimation* m_pCurrentAnimation;

public:
	CAnimator();
	~CAnimator();
	
	void CreateAnimation(tstring a_strKey, const tcchar* a_pFileName, CMesh* a_pMesh);
	CAnimation* GetAnimation(tstring a_strKey);
	void SetCurrentAnimation(tstring a_strKey);
	CAnimation* GetCurrentAnimation() { return this->m_pCurrentAnimation; }
};


#pragma once
#include "TMuffinSysInclude.h"
#include "Component/CComponentBase.h"

typedef void (*MuffinAnimationCallBack)(tstring a_strName, void* a_pCustom);

class CMesh;
class CAnimation;
class cSimpleAssimpSkinnedMesh;
class T_DLL_EXPORT CAnimator : public CComponentBase
{
private:
	vector<tstring> m_strFileName;
	hash_map<tstring, CAnimation*> m_mapName2Animation;
	CAnimation* m_pCurrentAnimation;
	MuffinAnimationCallBack m_pCallBack;
	void* m_pCallBackCustom;
	friend class CAnimation;

private:
	void CallBackEndAnimation();

protected:
	virtual void Init() override;

public:
	CAnimator();
	~CAnimator();
	
	CAnimation* CreateAnimation(tstring a_strKey, const tcchar* a_pFileName);
	CAnimation* GetAnimation(tstring a_strKey);
	void SetCurrentAnimation(tstring a_strKey);
	CAnimation* GetCurrentAnimation() { return this->m_pCurrentAnimation; }
	void SetCallBack(MuffinAnimationCallBack a_pCallBack, void* a_pCustom);
	tbool IsPlaying();
};


#pragma once
#include "TMuffinSysInclude.h"
#include "../TPhysics/TPhysics.h"

class CGUIDMaker;
class CGUIDMaker;
class CWindow;
class CGameObjectManager;
class CGraphicsWorld;
class CCameraManager;
class CLightManager;
class CPhysicsReactor;
class CAssetsPool;
class CAudioManager;

class CMuffin
{
private:
	tbool m_bRun;
	f64 m_fNowFrameTime;
	f32 m_fDeltaFrameTime;

	CGUIDMaker* m_pGUIDMaker;
	CWindow* m_pWindow;
	CGameObjectManager* m_pGameObjectManager;
	CGraphicsWorld* m_pGraphicsWorld;
	CCameraManager* m_pCameraManager;
	CLightManager* m_pLightManager;
	CAssetsPool* m_pAssetsPoolManager;
	CPhysicsWorld* m_pPhysicsWorld;
	CAudioManager* m_pAudioManager;


public:
	CMuffin();
	~CMuffin();

	T_INLINE void SetRun(tbool a_bRun) { this->m_bRun = a_bRun; }
	T_INLINE tbool IsRun() { return this->m_bRun; }
	T_INLINE f64 GetNowFrameTime() { return this->m_fNowFrameTime; }
	T_INLINE f32 GetDeltaFrameTime() { return this->m_fDeltaFrameTime; }

	T_INLINE CGUIDMaker* GetGUIDMaker() { return this->m_pGUIDMaker; }
	T_INLINE CWindow* GetWindow() { return this->m_pWindow; }
	T_INLINE CGameObjectManager* GetGameObjectMgr() { return this->m_pGameObjectManager; }
	T_INLINE CGraphicsWorld* GetGraphicsWorld() { return this->m_pGraphicsWorld; }
	T_INLINE CCameraManager* GetCameraMgr() { return this->m_pCameraManager; }
	T_INLINE CLightManager* GetLightMgr() { return this->m_pLightManager; }
	T_INLINE CAssetsPool* GetAssetsPoolMgr() { return this->m_pAssetsPoolManager; }
	T_INLINE CPhysicsWorld* GetPhysicsWorld() { return this->m_pPhysicsWorld; }
	T_INLINE CAudioManager* GetAudioMgr() { return this->m_pAudioManager; }


public:

	void Tick();

};

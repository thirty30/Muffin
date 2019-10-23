#pragma once

class CMuffin
{
private:
	tbool m_bRun;
	f64 m_fNowFrameTime;
	f32 m_fDeltaFrameTime;
	
	CGUIDMaker* m_pGUIDMaker;
	CWindow* m_pWindow;
	CGameObjectManager* m_pGameObjectManager;
	CCameraManager* m_pCameraManager;
	CLightManager* m_pLightManager;
	CObjectPhysics* m_pObjectPhysics;
	CParticleEmitterManager* m_pParticleEmitterManager;


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
	T_INLINE CCameraManager* GetCameraMgr() { return this->m_pCameraManager; }
	T_INLINE CLightManager* GetLightMgr() { return this->m_pLightManager; }
	T_INLINE CObjectPhysics* GetObjectPhysics() { return this->m_pObjectPhysics; }
	T_INLINE CParticleEmitterManager* GetParticleEmitterMgr() { return this->m_pParticleEmitterManager; }
	

public:
	
	void Tick();

};

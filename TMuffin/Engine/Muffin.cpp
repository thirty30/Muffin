#include "pch.h"

CMuffin::CMuffin()
{
	this->m_bRun = true;
	this->m_fNowFrameTime = 0;
	this->m_fDeltaFrameTime = 0;

	this->m_pGUIDMaker = new CGUIDMaker();
	this->m_pWindow = new CWindow();
	this->m_pGameObjectManager = new CGameObjectManager();
	this->m_pGraphicsRenderer = new CGraphicsRenderer();
	this->m_pCameraManager = new CCameraManager();
	this->m_pLightManager = new CLightManager();
	this->m_pPhysicsReactor = new CPhysicsReactor();
	this->m_pParticleEmitterManager = new CParticleEmitterManager();

}

CMuffin::~CMuffin()
{
	delete this->m_pGUIDMaker;
	delete this->m_pWindow;
	delete this->m_pGameObjectManager;
	delete this->m_pGraphicsRenderer;
	delete this->m_pCameraManager;
	delete this->m_pLightManager;
	delete this->m_pPhysicsReactor;
	delete this->m_pParticleEmitterManager;

	this->m_pGUIDMaker = NULL;
	this->m_pWindow = NULL;
	this->m_pGameObjectManager = NULL;
	this->m_pGraphicsRenderer = NULL;
	this->m_pCameraManager = NULL;
	this->m_pLightManager = NULL;
	this->m_pPhysicsReactor = NULL;
	this->m_pParticleEmitterManager = NULL;
}

void CMuffin::Tick()
{
	f64 fNowFrameTime = glfwGetTime();
	this->m_fDeltaFrameTime = (f32)(fNowFrameTime - this->m_fNowFrameTime);
	this->m_fNowFrameTime = fNowFrameTime;
	this->m_bRun = !this->m_pWindow->WindowShouldClose();
}


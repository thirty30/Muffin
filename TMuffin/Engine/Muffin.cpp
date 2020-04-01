#include "Muffin.h"
#include "Utility/CGUIDMaker.h"
#include "Window/CWindow.h"
#include "GameObject/CGameObjectManager.h"
#include "Graphics/CGraphicsWorld.h"
#include "Camera/CCameraManager.h"
#include "Light/CLightManager.h"
#include "AssetsLoader/CAssetsPool.h"
#include "../../TPhysics/PhysicsHelper.h"

CMuffin::CMuffin()
{
	this->m_bRun = true;
	this->m_fNowFrameTime = 0;
	this->m_fDeltaFrameTime = 0;

	this->m_pGUIDMaker = new CGUIDMaker(E_GUID_MAX);
	this->m_pWindow = new CWindow();
	this->m_pGameObjectManager = new CGameObjectManager();
	this->m_pGraphicsWorld = new CGraphicsWorld();
	this->m_pCameraManager = new CCameraManager();
	this->m_pLightManager = new CLightManager();
	this->m_pAssetsPoolManager = new CAssetsPool();
	this->m_pPhysicsWorld = new CPhysicsWorld();

}

CMuffin::~CMuffin()
{
	delete this->m_pGUIDMaker;
	delete this->m_pWindow;
	delete this->m_pGameObjectManager;
	delete this->m_pGraphicsWorld;
	delete this->m_pCameraManager;
	delete this->m_pLightManager;
	delete this->m_pAssetsPoolManager;
	delete this->m_pPhysicsWorld;

	this->m_pGUIDMaker = NULL;
	this->m_pWindow = NULL;
	this->m_pGameObjectManager = NULL;
	this->m_pGraphicsWorld = NULL;
	this->m_pCameraManager = NULL;
	this->m_pLightManager = NULL;
	this->m_pAssetsPoolManager = NULL;
	this->m_pPhysicsWorld = NULL;
}

void CMuffin::Tick()
{
	f64 fNowFrameTime = glfwGetTime();
	this->m_fDeltaFrameTime = (f32)(fNowFrameTime - this->m_fNowFrameTime);
	this->m_fNowFrameTime = fNowFrameTime;
	this->m_bRun = !this->m_pWindow->WindowShouldClose();
}


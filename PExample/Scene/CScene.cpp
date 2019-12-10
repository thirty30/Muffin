#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;
	this->m_pSkyBox = NULL;
	this->m_mapID2Actor.clear();
	this->m_pLuaState = NULL;
	this->m_vecLineTweenGroup.clear();
}

CScene::~CScene()
{

}

tbool CScene::Init()
{
	this->m_pCameraControl = new CCameraControl();
	this->m_pShipControl = new CShipControl();

	this->m_pLuaState = luaL_newstate();
 	luaL_openlibs(this->m_pLuaState);
 	lua_gc(this->m_pLuaState, LUA_GCSTOP, 0);
 
	lua_register(this->m_pLuaState, "CreateActor", CreateActor);
	lua_register(this->m_pLuaState, "AddLineTweenMove", AddLineTweenMove);
	lua_register(this->m_pLuaState, "AddLineTweenScale", AddLineTweenScale);
	lua_register(this->m_pLuaState, "AddLineTweenRotation", AddLineTweenRotation);
	lua_register(this->m_pLuaState, "AddLineTweenCurve", AddLineTweenCurve);
	lua_register(this->m_pLuaState, "AddLineTweenFollow", AddLineTweenFollow);
	lua_register(this->m_pLuaState, "AddControl", AddControl);
	lua_register(this->m_pLuaState, "AddToLineTweenGroup", ::AddToLineTweenGroup);
	lua_register(this->m_pLuaState, "LineTweenGroupFollow", ::LineTweenGroupFollow);

 	luaL_loadfile(this->m_pLuaState, "../LuaScripts/Main.lua");
	lua_pcall(this->m_pLuaState, 0, 0, 0);

	return true;
}

n32 CScene::GenGUID()
{
	return (++this->m_nGUIDIdx);
}

tbool CScene::LoadScene()
{
	//initialize camera
	n32 nScreenWidth = CGame::GetSingleton().GetScreenWidth();
	n32 nScreenHigh = CGame::GetSingleton().GetScreenHigh();
	f32 fScreenRatio = 1.0f * nScreenWidth / nScreenHigh;
	this->m_pCamera = new CCamera(this->GenGUID(), 0.6f, fScreenRatio, 3.0f, 100000.0f);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 200, -280);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 5, -10);
	//this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.8f, 1.0f));

	this->m_pCamera->m_vPosition = glm::vec3(0, 800, -1000);
	this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.5f, 1.0f));
	TMuffin_AddCamera(this->m_pCamera);

	//Mesh
	CMesh* pMeshCube = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_CUBE);
	CMesh* pMeshSphere = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE);
	CMesh* pMeshTerrain = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_TERRAIN);
	CMesh* pMeshTriangle = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_TRIANGLE);
	CMesh* pMeshSphereUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE_UV);
	CMesh* pMeshCubeUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_CUBE_UV);
	CMesh* pMeshTest = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_TEST);
	CMesh* pMeshSkyBox = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SKYBOX);
	CMesh* pMeshBunnyUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_BUNNY_UV);
	

	//SkyBox
	n32 nShaderSkyBox = CResourceManager::GetSingleton().GetShaderID(E_SHADER_ID_SKYBOX);
	this->m_pSkyBox = new CSkyBox();
	this->m_pSkyBox->Init(pMeshSkyBox, nShaderSkyBox,
		"../Assets/Textures/SkyBox/Space/SpaceBoxX.png", "../Assets/Textures/SkyBox/Space/SpaceBoxNegX.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxY.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegY.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxZ.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegZ.png"
		);
		//"../Assets/Textures/SkyBox/BlueSky/BlueSkyX.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegX.png",
		//"../Assets/Textures/SkyBox/BlueSky/BlueSkyY.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegY.png",
		//"../Assets/Textures/SkyBox/BlueSky/BlueSkyZ.png", "../Assets/Textures/SkyBox/BlueSky/BlueSkyNegZ.png");
	TMuffin_SetSkyBox(this->m_pSkyBox);

	//pSkyBox->LoadTextures("../Assets/Textures/SkyBox/Space/SpaceBox_right1_posX.bmp", "../Assets/Textures/SkyBox/Space/SpaceBox_left2_negX.bmp",
	//	"../Assets/Textures/SkyBox/Space/SpaceBox_top3_posY.bmp", "../Assets/Textures/SkyBox/space/SpaceBox_bottom4_negY.bmp",
	//	"../Assets/Textures/SkyBox/Space/SpaceBox_front5_posZ.bmp", "../Assets/Textures/SkyBox/space/SpaceBox_back6_negZ.bmp");

	//scene items
	CDirectionLight* pDirectionLight = new CDirectionLight();

	//CPointLight* pPointLight1 = new CPointLight();
	//pPointLight1->m_vPosition = glm::vec3(100.0f, -100.0f, 30.0f);
	//pPointLight1->m_fLinear = 0.01f;
	//pPointLight1->m_fDistanceCutOff = 1000.0f;
	
	//lua_getglobal(this->m_pLuaState, "DistributeEvent");
	//lua_pushnumber(this->m_pLuaState, 1);
	//lua_pcall(this->m_pLuaState, 1, 0, 0);

	CZone* pZone = new CZone();
	pZone->m_vPosition = glm::vec3(900.0f, 0.0f, 350.0f);
	pZone->CreateCollider(E_COLLIDER_TYPE_SPHERE);


	//CActor* pActor = new CActor();
	//CMaterialStandard* pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BUNNY);
	//CTexture* pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_CIRCLE);
	//pMaterial->AddTexture(pTexture);
	//pActor->InitRenderer(pMeshBunnyUV, pMaterial);
	//
	//CLineTweenMove* pLineTween = (CLineTweenMove*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_MOVE_TO);
	//pLineTween->Init(pActor->m_vPosition, glm::vec3(-400.0f, 0.0f, 400.0f), 100.0f, 0.0f);
	//
	//{
	//	CActor* a = new CActor();
	//	CMaterialStandard* m = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_DEFAULT);
	//	m->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//	a->InitRenderer(pMeshSphere, m);
	//	a->m_vPosition = glm::vec3(-400.0f, 0.0f, 400.0f);
	//}
	//
	//CLineTweenScale* pLineTween2 = (CLineTweenScale*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_SCALE_TO);
	//pLineTween2->Init(pActor->m_vScale, glm::vec3(2.0f, 2.0f, 2.0f), 1.0f);
	//
	//CLineTweenRotation* pLineTween3 = (CLineTweenRotation*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_ROTATE_TO);
	//pLineTween3->Init(pActor->GetEulerAngle(), glm::vec3(0.0f, 180.0f, 0.0f), 2.0f);
	//
	//CShipControl::GetSingleton().pActor = pActor;
	//
	//CActor* pActor1 = new CActor();
	//pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BUNNY);
	//pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_CIRCLE);
	//pMaterial->AddTexture(pTexture);
	//pActor1->InitRenderer(pMeshBunnyUV, pMaterial);
	//pActor1->m_vPosition = glm::vec3(100.0f, 0.0f, 200.0f);
	//
	//CLineTweenFollow* pLineTween4 = (CLineTweenFollow*)pActor1->CreateSerialLineTween(E_LINETWEEN_TYPE_FOLLOW);
	//pLineTween4->Init(pActor, 30.0f, 100.0f);
	//
	//CActor* pActor2 = new CActor();
	//pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BUNNY);
	//pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_CIRCLE);
	//pMaterial->AddTexture(pTexture);
	//pActor2->InitRenderer(pMeshBunnyUV, pMaterial);
	//pActor2->m_vPosition = glm::vec3(100.0f, 0.0f, 0.0f);
	//
	//glm::vec3 p1 = pActor2->m_vPosition + glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 p2 = pActor2->m_vPosition + glm::vec3(500.0f, 200.0f, 100.0f);
	//glm::vec3 p3 = pActor2->m_vPosition + glm::vec3(0.0f, 0.0f, 500.0f);
	//
	//CLineTweenCurve* pLineTween5 = (CLineTweenCurve*)pActor2->CreateSerialLineTween(E_LINETWEEN_TYPE_CURVE);
	//pLineTween5->Init(p1, p2, p3, 3.0f);
	
	glm::vec3 p1 = glm::vec3(100.0f, 0.0f, 0.0f);
	glm::vec3 p2 = glm::vec3(600.0f, 200.0f, 100.0f);
	glm::vec3 p3 = glm::vec3(100.0f, 0.0f, 500.0f);
	vector<glm::vec3> pointArray = GenerateBezierCurve(p1, p2, p3);
	for (n32 i = 0; i < pointArray.size(); i++)
	{
		CActor* a = new CActor();
		CMaterialStandard* m = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_DEFAULT);
		m->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		a->InitRenderer(pMeshSphere, m);
		a->m_vPosition = pointArray[i];
		//a->m_vScale = glm::vec3(10.0f, 10.0f, 10.0f);
	}


	return true;
}

void CScene::Clear()
{
	if (this->m_pCamera != NULL)
	{
		delete this->m_pCamera;
	}
	if (this->m_pCameraControl != NULL)
	{
		delete this->m_pCameraControl;
	}
	lua_close(this->m_pLuaState);
}

void CScene::Loop()
{
	//this->m_pShip->Update();
}

CActor* CScene::NewActor()
{
	CActor* pActor = new CActor();
	pActor->CreateCollider(E_COLLIDER_TYPE_SPHERE);
	CMaterialStandard* pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BUNNY);
	CTexture* pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_CIRCLE);
	pMaterial->AddTexture(pTexture);
	CMesh* pMeshBunnyUV = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_BUNNY_UV);
	pActor->InitRenderer(pMeshBunnyUV, pMaterial);
	pActor->m_nActorID = this->GenGUID();
	this->m_mapID2Actor[pActor->m_nActorID] = pActor;
	return pActor;
}

CActor* CScene::FindActor(n32 a_nActorID)
{
	hash_map<u64, CActor*>::const_iterator iter = this->m_mapID2Actor.find(a_nActorID);
	if (iter == this->m_mapID2Actor.end())
	{
		return NULL;
	}
	return iter->second;
}

void CScene::AddToLineTweenGroup(n32 a_nActorID)
{
	CActor* pActor = this->FindActor(a_nActorID);
	if (pActor == NULL)
	{
		return;
	}
	this->m_vecLineTweenGroup.push_back(pActor);
}

void CScene::LineTweenGroupFollow(n32 a_nTargetID, f32 a_fDis, f32 a_fVelocity)
{
	CActor* pTargetActor = this->FindActor(a_nTargetID);
	if (pTargetActor == NULL)
	{
		return;
	}

	for (n32 i = 0; i < this->m_vecLineTweenGroup.size(); i++)
	{
		CActor* pActor = this->m_vecLineTweenGroup[i];

		CLineTweenFollow* pLineTween = (CLineTweenFollow*)pActor->CreateParallelLineTween(E_LINETWEEN_TYPE_FOLLOW);
		pLineTween->Init(pTargetActor, a_fDis, a_fVelocity);
	}
}


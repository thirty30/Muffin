#include "ExportFunction.h"
#include "Engine.h"
#include "Camera/CCamera.h"
#include "Camera/CCameraManager.h"
#include "Graphics/SkyBox/CSkyBox.h"
#include "Graphics/CGraphicsWorld.h"

tbool TMuffin_Initialize(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	return MuffinInit(a_nWinWidth, a_nWinHigh, a_strWinName);
}
void TMuffin_Loop()
{
	MuffinMainLoop();
}
void TMuffin_Clear()
{
	MuffinClear();
}

#define TMUFFIN_REGISTER_CALLBACK(FUNC_NAME, FUNC_TYPE, FUNC_VARIABLE) FUNC_TYPE FUNC_VARIABLE = NULL; \
	void FUNC_NAME(FUNC_TYPE a_func) { FUNC_VARIABLE = a_func; }

TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterKeyCallback, MuffinKeyCallBack, pExternalKeyCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterMouseCallback, MuffinMouseCallBack, pExternalMouseCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterCursorCallback, MuffinCursorCallBack, pExternalCursorCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterScrollCallback, MuffinScrollCallBack, pExternalScrollCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterPhysicsCallBack, MuffinPhysicsCallBack, pExternalGameLogicCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterGameLogicCallBack, MuffinGameLogicCallBack, pExternalPhysicsCallBack)

f64 TMuffin_GetNowFrameTime()
{
	return MUFFIN.GetNowFrameTime();
}
f32 TMuffin_GetDeltaFrameTime()
{
	return MUFFIN.GetDeltaFrameTime();
}

void TMuffin_SetSkyBox(const tcchar* a_strMeshFile,
	const tcchar* a_strVertexShader, const tcchar* a_strFragmentShader,
	const tcchar* a_strXTexture, const tcchar* a_strNegXTexture,
	const tcchar* a_strYTexture, const tcchar* a_strNegYTexture,
	const tcchar* a_strZTexture, const tcchar* a_strNegZTexture)
{
	CSkyBox* pSkyBox = new CSkyBox();
	pSkyBox->Init(a_strMeshFile,
		a_strVertexShader, a_strFragmentShader,
		a_strXTexture, a_strNegXTexture,
		a_strYTexture, a_strNegYTexture,
		a_strZTexture, a_strNegZTexture
	);
	MUFFIN.GetGraphicsWorld()->SetSkyBox(pSkyBox);
}


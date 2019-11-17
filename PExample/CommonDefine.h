#pragma once

enum EModelID
{
	E_MODEL_ID_UNKNOWN = 0,

	E_MODEL_ID_SKYBOX,
	E_MODEL_ID_TERRAIN,
	E_MODEL_ID_CUBE,
	E_MODEL_ID_SPHERE,
	E_MODEL_ID_TRIANGLE,
	E_MODEL_ID_SPHERE_UV,
	E_MODEL_ID_CUBE_UV,
	E_MODEL_ID_BUNNY_UV,
	E_MODEL_ID_TEST,
};

enum EShaderID
{
	E_SHADER_ID_UNKNOWN = 0,

	E_SHADER_ID_DEFAULT,
	E_SHADER_ID_STANDARD,
	E_SHADER_ID_SKYBOX,
	E_SHADER_ID_BUNNY,

	E_SHADER_ID_MAX,
};

enum EMaterialID
{
	E_MATERIAL_ID_UNKNOWN = 0,

	E_MATERIAL_ID_DEFAULT,
	E_MATERIAL_ID_STANDARD,
	E_MATERIAL_ID_BUNNY,
};

enum ETextureID
{
	E_TEXTURE_ID_UNKNOWN = 0,
	E_TEXTURE_ID_CIRCLE,


	E_TEXTURE_ID_TEST, //"../Assets/Textures/leaf.png"
	E_TEXTURE_ID_TEST2, //"../Assets/Textures/leaf2.png"
};

enum EGameStatus
{
	E_GAME_STATUS_INIT = 0,

	E_GAME_STATUS_LOAD_SCENE_START,
	E_GAME_STATUS_LOAD_SCENE_FINISH,
};



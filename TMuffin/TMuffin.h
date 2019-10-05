#pragma once

#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>						// glm::vec3
#include <glm/vec4.hpp>						// glm::vec4
#include <glm/mat4x4.hpp>					// glm::mat4
#include <glm/gtc/matrix_transform.hpp>		// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>				// glm::value_ptr

///////////////////////////////////////////////////////////////////////////////////////

#include "./CommonDefine.h"
#include "./Window/CWindow.h"
#include "./Object/CMuffinObject.h"
#include "./Camera/CCamera.h"
#include "./Camera/CCameraManager.h"
#include "./Mesh/CMesh.h"
#include "./Renderer/CMeshRenderer.h"
#include "./ShaderHelper/CShaderHelper.h"
#include "./Object/CGameObject.h"
#include "./Object/CGameObjectManager.h"
#include "./ResourceLoader/CResourceLoader.h"

#include "./TMuffinDeclare.h"


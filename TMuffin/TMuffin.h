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
#include "./Utility/CGUIDMaker.h"
#include "./ShaderHelper/CShaderHelper.h"
#include "./Light/CLight.h"
#include "./Light/CLightManager.h"
#include "./Mesh/CMesh.h"

#include "./Texture/cBasicTextureManager.h"
#include "./Texture/CTexutre.h"

#include "./GameObject/CGameObject.h"
#include "./GameObject/CGameObjectManager.h"
#include "./Camera/CCamera.h"
#include "./Camera/CCameraManager.h"
#include "./Graphics/CGraphicsObject.h"
#include "./Graphics/CGraphicsRenderer.h"

#include "./Physics/CRigidBody.h"
#include "./Physics/CCollider.h"
#include "./Physics/CPhysicsObject.h"
#include "./Physics/PhysicsHelper.h"
#include "./Physics/CPhysicsReactor.h"

#include "./Particle/CParticle.h"
#include "./Particle/CParticleEmitter.h"
#include "./Particle/CParticleEmitterManager.h"

#include "./Window/CWindow.h"
#include "./ResourceLoader/CResourceLoader.h"
#include "./Engine/ExportFunction.h"
#include "./Engine/Muffin.h"
#include "./Engine/Engine.h"



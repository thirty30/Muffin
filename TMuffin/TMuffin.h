#pragma once

#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>						// glm::v-ec3
#include <glm/vec4.hpp>						// glm::vec4
#include <glm/mat4x4.hpp>					// glm::mat4
#include <glm/gtc/matrix_transform.hpp>		// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>				// glm::value_ptr
#include <glm/gtx/vector_angle.hpp>
#include <FreeImage/FreeImage.h>
#include <rapidjson/document.h>
///////////////////////////////////////////////////////////////////////////////////////

#include "./CommonDefine.h"
#include "./Utility/CGUIDMaker.h"
#include "./Utility/Utility.h"
#include "./ShaderHelper/CShaderHelper.h"
#include "./Light/CLight.h"
#include "./Light/CLightManager.h"
#include "./Mesh/CMesh.h"

#include "./Texture/CTexture.h"
#include "./Material/CMaterialBase.h"
#include "./Material/CMaterial.h"
#include "./Material/CMaterialDefault.h"
#include "./Material/CMaterialStandard.h"

#include "./GameObject/CGameObject.h"
#include "./GameObject/CGameObjectManager.h"
#include "./Camera/CCamera.h"
#include "./Camera/CCameraManager.h"
#include "./Graphics/CGraphicsObject.h"
#include "./SkyBox/CSkyBox.h"
#include "./Graphics/CGraphicsRenderer.h"

#include "./Physics/CRigidBody.h"
#include "./Physics/PhysicsDefine.h"
#include "./Physics/CColliderBase.h"
#include "./Physics/CColliderPlane.h"
#include "./Physics/CColliderSphere.h"
#include "./Physics/CColliderBox.h"
#include "./Physics/CColliderCapsule.h"
#include "./Physics/CColliderMesh.h"
#include "./Physics/PhysicsHelper.h"
#include "./Physics/CPhysicsObject.h"
#include "./Physics/CPhysicsReactor.h"

#include "./Particle/CParticle.h"
#include "./Particle/CParticleEmitter.h"
#include "./Particle/CParticleEmitterManager.h"

#include "./LineTween/CLineTween.h"
#include "./LineTween/CLineTweenMove.h"
#include "./LineTween/CLineTweenScale.h"
#include "./LineTween/CLineTweenRotation.h"
#include "./LineTween/CLineTweenCurve.h"
#include "./LineTween/CLineTweenFollow.h"

#include "./Window/CWindow.h"
#include "./ResourceLoader/CResourceLoader.h"
#include "./Engine/ExportFunction.h"
#include "./Engine/Muffin.h"
#include "./Engine/Engine.h"



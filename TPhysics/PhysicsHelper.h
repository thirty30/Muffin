#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"

T_DLL_EXPORT void CalcColliderIsHit(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo);
T_DLL_EXPORT void doSphere2Plane(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo);
T_DLL_EXPORT void doSphere2Sphere(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo);
T_DLL_EXPORT void doSphere2Box(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo);
T_DLL_EXPORT void doSphere2Cloth(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo);
T_DLL_EXPORT void RK4(glm::vec3& a_vPosition, glm::vec3& a_vVelocity, glm::vec3& a_vAcc, f32 a_fDT);

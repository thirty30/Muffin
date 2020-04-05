#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"

namespace TPhysics
{
	class CBodyBase;
	class CColliderBase;
	class T_DLL_EXPORT CPhysicsObject
	{
	private:
		u64 m_nGUID;
		CBodyBase* m_pBody;
		glm::vec3 m_vPrePosition;
		CColliderBase* m_pCollider;
		TPhyOnCollision m_funcCallBack;

	private:
		virtual void OnCollision(SCollisionInfo& a_rCollision) 
		{
			if (this->m_funcCallBack != NULL)
			{
				this->m_funcCallBack(a_rCollision);
			}
		}
		void RefreshColliderPostion();

		friend class CPhysicsWorld;

	public:
		glm::vec3 m_vNowPosition;

	public:
		tbool m_bIsEnable;
		void* m_pCustomData;
		tstring m_strTag;

		CPhysicsObject();
		~CPhysicsObject();

		T_INLINE u64 GetGUID() { return this->m_nGUID; }

		EBodyType GetBodyType();
		EColliderType GetColliderType();
		glm::vec3 GetPosition() { return this->m_vNowPosition; }
		void SetPosition(glm::vec3 a_vPosition) { this->m_vNowPosition = a_vPosition; }
		void SetOnCollisionCallBack(TPhyOnCollision a_func) { this->m_funcCallBack = a_func; }

		template<typename T>
		T* CreateCollider();
		template<typename T>
		T* GetCollider();
		template<typename T>
		T* CreateBody();
		template<typename T>
		T* GetBody();
	};

	template<typename T>
	T* CPhysicsObject::CreateCollider()
	{
		this->m_pCollider = new T();
		return static_cast<T*>(this->m_pCollider);
	}

	template<typename T>
	T* CPhysicsObject::GetCollider()
	{
		if (this->m_pCollider == NULL) { return NULL; }
		return static_cast<T*>(this->m_pCollider);
	}

	template<typename T>
	T* CPhysicsObject::CreateBody()
	{
		this->m_pBody = new T();
		return static_cast<T*>(this->m_pBody);
	}

	template<typename T>
	T* CPhysicsObject::GetBody()
	{
		if (this->m_pBody == NULL) { return NULL; }
		return static_cast<T*>(this->m_pBody);
	}

}


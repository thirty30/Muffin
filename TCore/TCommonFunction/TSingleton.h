#pragma once

namespace TCore
{
	namespace TSingleton
	{
		template<typename T>
		class CSingleton
		{
		protected:
			static T* m_pSingleton;

		public:
			CSingleton()
			{
				m_pSingleton = static_cast<T*>(this);
			}
			virtual ~CSingleton()
			{
				m_pSingleton = NULL;
			}
			static T& GetSingleton()
			{
				return *m_pSingleton;
			}
			static T* GetSingletonPtr()
			{
				return m_pSingleton;
			}
		};

#define T_IMPLEMENT_SINGLETON( SingletonClass )\
	template<> SingletonClass* CSingleton<SingletonClass>::m_pSingleton = NULL;
	}
}

using namespace TCore::TSingleton;


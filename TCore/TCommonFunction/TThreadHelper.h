#pragma once

namespace TCore
{
	namespace TThreadHelper
	{
		class TThreadInterface
		{
		public:
			virtual void Run() T_PURE;
		};

		class TThreadWorker
		{
		private:
			TThreadInterface * m_pRunner;
			HANDLE m_pHandle;

		public:
			TThreadWorker(TThreadInterface* a_pRunner)
			{
				this->m_pRunner = a_pRunner;
				this->m_pHandle = NULL;
			}
			static DWORD WINAPI TThreadWorkerCallBack(LPVOID a_pRunner)
			{
				((TThreadInterface*)a_pRunner)->Run();
				return 0;
			}

			tbool CreateThread()
			{
				this->m_pHandle = ::CreateThread(NULL, 0, TThreadWorker::TThreadWorkerCallBack, m_pRunner, 0, NULL);
				return true;
			}

			void Stop()
			{
				TerminateThread(m_pHandle, 0);
			}
		};

		class TThreadCriticalSection
		{
		private:
			CRITICAL_SECTION m_section;

		public:
			TThreadCriticalSection()
			{
				InitializeCriticalSection(&this->m_section);
			}

			~TThreadCriticalSection()
			{
				DeleteCriticalSection(&this->m_section);
			}

			void Lock()
			{
				EnterCriticalSection(&this->m_section);
			}

			void UnLock()
			{
				LeaveCriticalSection(&this->m_section);
			}

		};

		class TThreadMutexLock
		{
		private:
			HANDLE m_lock;

		public:
			TThreadMutexLock()
			{
				m_lock = CreateMutex(NULL, FALSE, NULL);
			}

			~TThreadMutexLock()
			{
				CloseHandle(m_lock);
			}

			void Lock()
			{
				WaitForSingleObject(m_lock, INFINITE);
			}

			void UnLock()
			{
				ReleaseMutex(m_lock);
			}

		};
	}
}

using namespace TCore::TThreadHelper;


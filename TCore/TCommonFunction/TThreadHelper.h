#pragma once

namespace TCore
{
	namespace TThreadHelper
	{
		//线程基类
		class TThreadInterface
		{
		public:
			virtual void Run() T_PURE;
		};

		//线程类
		class TThreadWorker
		{
		private:
			TThreadInterface * m_pRunner;
			HANDLE m_tID;
		public:
			TThreadWorker(TThreadInterface* a_pRunner)
			{
				m_pRunner = a_pRunner;
			}
			static DWORD WINAPI TThreadWorkerCallBack(LPVOID a_pRunner)
			{
				((TThreadInterface*)a_pRunner)->Run();
				return 0;
			}

			tbool CreateThread()
			{
				HANDLE m_tID = ::CreateThread(NULL, 0, TThreadWorker::TThreadWorkerCallBack, m_pRunner, 0, NULL);
				return true;
			}

			void Stop()
			{
				TerminateThread(m_tID, 0);
			}
		};

		//互斥锁
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


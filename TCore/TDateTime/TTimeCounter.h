#pragma once 

namespace TCore
{
	namespace TTime
	{
		class T_DLL_API TTimeCounter
		{
		public:
			n64 m_nFrequency;
			n64 m_nStart;
			n64 m_nCurrent;

			T_INLINE TTimeCounter()
			{
				m_nFrequency = 0;
				m_nStart = 0;
				m_nCurrent = 0;

				//得到时钟频率
				LARGE_INTEGER nFreq;
				TMemzero(&nFreq, sizeof(LARGE_INTEGER));
				QueryPerformanceFrequency(&nFreq);
				m_nFrequency = nFreq.QuadPart;		//n times per second
				
				LARGE_INTEGER nStart;
				TMemzero(&nStart, sizeof(LARGE_INTEGER));
				QueryPerformanceCounter(&nStart);
				m_nStart = nStart.QuadPart;
			}
			
			~TTimeCounter()
			{

			}

			T_INLINE void UpdateCounter()
			{
				LARGE_INTEGER nCur;
				TMemzero(&nCur, sizeof(LARGE_INTEGER));
				QueryPerformanceCounter(&nCur);
				m_nCurrent = nCur.QuadPart;
			}

			T_INLINE f64 GetCurrentFramesTime()
			{
				UpdateCounter();
				return (f64)(m_nCurrent - m_nStart) / m_nFrequency;
			}
		};
	}
}




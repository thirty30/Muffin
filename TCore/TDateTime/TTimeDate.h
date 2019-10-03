#pragma once 

namespace TCore
{
	namespace TTime
	{
		class T_DLL_API TTimeDate
		{
		private:
			tm m_utc;
		public:
			TTimeDate()
			{
				TTimestamp m_stamp;
				time_t t = m_stamp.GetSTime();
				gmtime_s(&m_utc, &t);

			}
			~TTimeDate(){}

			//秒数[0~59]
			T_INLINE n32 GetSecond()
			{
				return m_utc.tm_sec;
			}
			//分钟[0~59]
			T_INLINE n32 GetMinute()
			{
				return m_utc.tm_min;
			}
			//小时[0~23]
			T_INLINE n32 GetHour()
			{
				return m_utc.tm_hour;
			}
			//月份日期[1~31]
			T_INLINE n32 GetMonthDay()
			{
				return m_utc.tm_mday;
			}
			//月份[1~12]
			T_INLINE n32 GetMonth()
			{
				return m_utc.tm_mon + 1;
			}
			//年份[1900~]
			T_INLINE n32 GetYear()
			{
				return m_utc.tm_year + 1990;
			}
			//每周日期[1~7]
			T_INLINE n32 GetWeekDay()
			{
				return (m_utc.tm_wday != 0) ? m_utc.tm_wday : 7;
			}
			//年份日期[1~366]
			T_INLINE n32 GetYearDay()
			{
				return m_utc.tm_yday + 1;
			}

			T_INLINE void FormatDate(tcchar* a_oBuffer, n32 a_nSize)
			{
				tcchar* pBuffer = TFormat("%04d%02d%02d_%02d%02d%02d",
					GetYear(), GetMonth(), GetMonthDay(),
					GetHour(), GetMinute(), GetSecond());
				TMemcpy(a_oBuffer, a_nSize, pBuffer, TStrlen(pBuffer));
			}
		};
	}
}



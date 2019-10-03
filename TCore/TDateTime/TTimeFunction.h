#pragma once 

namespace TCore
{
	namespace TTime
	{
		T_INLINE u32 TGetTimeStamp()
		{
			TTimestamp stamp;
			return stamp.GetStamp();
		}

		T_INLINE n32 TGetDifferDays(u32 a_uTime1, u32 a_uTime2)
		{
			n32 nDays1 = (a_uTime1 + TIME_ZONE_SPANS) / 86400;
			n32 nDays2 = (a_uTime2 + TIME_ZONE_SPANS) / 86400;
			return abs(nDays1 - nDays2);
		}
	}
}

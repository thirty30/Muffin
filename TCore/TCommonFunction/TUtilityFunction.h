#pragma once

namespace TCore
{
	namespace TMemoryFunction
	{
		/////////////////////////////内存函数////////////////////////////////////
		T_INLINE tbool TMemcpy(void* a_pDest, u32 a_nDestLen, const void* a_pSrc, u32 a_nSrcLen)
		{
			memcpy_s(a_pDest, a_nDestLen, a_pSrc, a_nSrcLen);
			return true;
		}

		T_INLINE n32 TMemcmp(const void* a_pBuffer1, const void* a_pBuffer2, u32 a_nLen)
		{
			return memcmp(a_pBuffer1, a_pBuffer2, a_nLen);
		}

		T_INLINE void TMemset(void* a_pDest, n32 a_nData, u32 a_nLen)
		{
			memset(a_pDest, a_nData, a_nLen);
		}

		T_INLINE void TMemzero(void* a_pDest, u32 a_nLen)
		{
			memset(a_pDest, 0, a_nLen);
		}


		///////////////////////////字符串函数(单字节)//////////////////////////////
		T_INLINE tbool TStrcpy(tcchar* a_pDest, u32 a_nDestLen, const tcchar* a_pSrc)
		{
			if (a_nDestLen >= strlen(a_pSrc))
			{
				strcpy_s(a_pDest, a_nDestLen, a_pSrc);
			}
			else
			{
				return false;
			}
			return true;
		}

		//分割字符串，该函数线程安全
		T_INLINE tcchar* TStrtok(tcchar* a_pToken, const tcchar* a_pDelimit, tcchar** a_pContext)
		{
			return strtok_s(a_pToken, a_pDelimit, a_pContext);
		}

		T_INLINE n32 TStrcmp(const tcchar* a_pStr1, const tcchar* a_pStr2)
		{
			return strcmp(a_pStr1, a_pStr2);
		}

		//大小写不敏感的字符串比较
		T_INLINE n32 TStricmp(const tcchar* a_pStr1, const tcchar* a_pStr2)
		{
			return _stricmp(a_pStr1, a_pStr2);
		}

		//比较字符串的前n个字符
		T_INLINE n32 TStrncmp(const tcchar* a_pStr1, const tcchar* a_pStr2, u32 a_nLen)
		{
			return strncmp(a_pStr1, a_pStr2, a_nLen);
		}

		T_INLINE n32 TStrnicmp(const tcchar* a_pStr1, const tcchar* a_pStr2, u32 a_nLen)
		{
			return _strnicmp(a_pStr1, a_pStr2, a_nLen);
		}

		T_INLINE u32 TStrlen(const tcchar* a_pStr)
		{
			return strlen(a_pStr);
		}


		T_INLINE n32 TToLower(const tcchar& a_cChar)
		{
			return tolower(a_cChar);
		}

		T_INLINE n32 TToUpper(const tcchar& a_cChar)
		{
			return toupper(a_cChar);
		}

		T_INLINE const tcchar* TStrchr(const tcchar* a_pStr, const tcchar& a_cChar)
		{
			return strchr(a_pStr, a_cChar);
		}

		T_INLINE const tcchar* TStrstr(const tcchar* a_pStr, const tcchar* a_pSearch)
		{
			return strstr(a_pStr, a_pSearch);
		}

		T_INLINE n32 TA2N32(const tcchar* a_pStr)
		{
			return atoi(a_pStr);
		}

		T_INLINE n64 TA2N64(const tcchar* a_pStr)
		{
			return _strtoi64(a_pStr, 0, 10);
		}

		T_INLINE u64 TA2U64(const tcchar* a_pStr)
		{
			return _strtoui64(a_pStr, 0, 10);
		}

		T_INLINE f64 TA2F(const tcchar* a_pStr)
		{
			return atof(a_pStr);
		}

		T_INLINE n32 TSprintf(tcchar* a_pBuffer, u32 a_nBufSize, const tcchar* a_pFormat, ...)
		{
			va_list parm;
			va_start(parm, a_pFormat);
			n32 res = vsprintf_s(a_pBuffer, a_nBufSize, a_pFormat, parm);
			va_end(parm);
			return res;
		}

// 		T_INLINE void TSscanf(tcchar* a_pBuffer, const tcchar* a_pFormat, ...)
// 		{
// 			va_list parm;
// 			va_start(parm, a_pFormat);
// 			sscanf_s(a_pBuffer, a_pFormat, parm);
// 			va_end(parm);
// 		}

#define FORMAT_TEMP_BUFFER_LEN 4096

		template<typename T>
		class CStringBufferHelper
		{
		public:
			T m_buffer[FORMAT_TEMP_BUFFER_LEN];
			CStringBufferHelper()
			{
				TMemzero(m_buffer, sizeof(m_buffer));
			}
		public:
			explicit CStringBufferHelper(const T* a_pFormat, va_list a_pParms)
			{
				vsprintf_s((tcchar*)m_buffer, FORMAT_TEMP_BUFFER_LEN - 1, (const tcchar*)a_pFormat, a_pParms);
			}

			T* GetBuffer(){ return m_buffer; }
		};

		template<typename T>
		T_INLINE CStringBufferHelper<T> TFormatHelper(const T* a_pFormat, ...)
		{
			va_list parms;
			va_start(parms, a_pFormat);
			CStringBufferHelper<T> obj = CStringBufferHelper<T>(a_pFormat, parms);
			va_end(parms);
			return obj;
		}

		//格式化字符串，线程安全
#define TFormat(...) TFormatHelper(__VA_ARGS__).GetBuffer()

		T_INLINE void TSleep(n32 a_msec)
		{
			Sleep(a_msec);
		}

		template <class T>
		T TRandInRange(T a_Min, T a_Max)
		{
			f64 value = a_Min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (static_cast<double>(a_Max - a_Min))));
			return static_cast<T>(value);
		}
	}
}

using namespace TCore::TMemoryFunction;

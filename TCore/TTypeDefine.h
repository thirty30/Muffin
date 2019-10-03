#pragma once

#define T_DLL_EXPORT _declspec(dllexport)
#define T_DLL_IMPORT _declspec(dllimport)

#ifdef T_EXPORTS
	#define T_DLL_API T_DLL_EXPORT
#else
	#define T_DLL_API T_DLL_IMPORT
#endif

#define T_INLINE inline
#define T_PURE = 0

namespace TCore
{
	namespace TypeDefine
	{
		typedef char					n8;
		typedef short					n16;
		typedef int						n32;
		typedef long long				n64;

		typedef unsigned char			u8;
		typedef unsigned short			u16;
		typedef unsigned int			u32;
		typedef unsigned long long		u64;

		typedef float					f32;
		typedef double					f64;
		
		typedef char					tcchar;
		typedef wchar_t					twchar;
		typedef string					tstring;

		typedef bool					tbool;
	}
}

using namespace TCore::TypeDefine;




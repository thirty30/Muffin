#pragma once

#ifndef _WIN32_WINNT            // 指定要求的最低平台是Windows7
#define _WIN32_WINNT 0x0601     // 将此值更改为相应的值以适用于Windows的其他版本。
#endif

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <math.h>
#include <stdarg.h>		//包含省略参数va_list va_start等的头文件
#include <time.h>
using namespace std;

#include <windows.h>
#include <io.h>
#include <share.h>

/////////////////////////使用stlport里面的结构////////////////////////
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <hash_set>
//#include <unordered_set>
//#include <unordered_map>

//////////////////////////////////////////////////////////////////////////

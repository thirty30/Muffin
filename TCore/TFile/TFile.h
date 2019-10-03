#pragma once

#define TFileOpen _fsopen
#define TFileClose fclose


//打开模式有b和没有b的区别
//windows下：
//有b:二进制的方式把字节都读出来，如果换行是/r/n那么会读出/r/n 是2个字节
//没有b：文本形式读出来，如果换行是/r/n 读出来只有/n 是1个字节
//linux下：
//结尾是\r\n，有没有b的方式，都会把两个字符读出来，没有区别

enum EFileMode
{
	E_FILE_CREATE_NEW	= 1,		//wb
	E_FILE_READ			= 2,		//r		文本读 尽量不用
	E_FILE_WRITE		= 3,		//w		文本写 尽量不用
	E_FILE_APPEND		= 4,		//a		文本追加 尽量不用
	E_FILE_B_READ		= 5,		//rb
	E_FILE_B_WRITE		= 6,		//wb
	E_FILE_B_APPEND		= 7,		//ab
};

enum ESeekOrigin
{
	E_FILE_SEEK_BEGIN	= SEEK_SET,
	E_FILE_SEEK_CURRENT	= SEEK_CUR,
	E_FILE_SEEK_END		= SEEK_END,
};

#include "./TFileObject.h"
#include "./TFileConfig.h"

using namespace TCore::TFile;



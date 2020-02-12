#pragma once
#include "TMuffinSysInclude.h"
#include <Thread>
class CMesh;
class T_DLL_EXPORT CResourceLoader
{
public:
	tbool LoadModelFromPly(const tcchar* a_strFileName, CMesh* a_pMesh);	//discarded function
	tbool LoadModelFromPlyUV(const tcchar* a_strFileName, CMesh* a_pMesh);	//discarded function
	tbool LoadMesh(const tcchar* a_strFileName, CMesh* a_pMesh);
	void ThreadTeset()
	{
		f32 x, y = 1.0f;
		std::thread simple_thread(
			[]
			()
			{
				for (auto i = 0; i < 1000; i++)
				{
					cout << "aaaaaaaa" << endl;
				}
			}
		);

		if (simple_thread.joinable())
		{
			simple_thread.join();
		}
	}
};


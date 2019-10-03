#include "stdafx.h"

bool gMainLoopRun = false;

int main(n32 argc, gcchar** argv)
{
	//init window
	CWindow* pWindow = new CWindow();
	if (pWindow->InitWindow() == false)
	{
		return 0;
	}

	gMainLoopRun = true;
	while (gMainLoopRun == true)
	{

	}

	//clear window
	pWindow->Clear();
	delete pWindow;

	return 0;
}

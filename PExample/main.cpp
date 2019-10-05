#include "stdafx.h"


n32 main(n32 argc, tcchar** argv)
{
	CGame* pGame = new CGame();
	pGame->SetScreenSize(1600, 990);
	if (pGame->InitGame() == false)
	{
		return 0;
	}

	LoopMuffin();
	
	pGame->ClearGame();
	delete pGame;

	return 0;
}



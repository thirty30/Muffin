#include "stdafx.h"

n32 main(n32 argc, tcchar** argv)
{
	CGame* pGame = new CGame();
	if (pGame->InitGame() == false)
	{
		return 0;
	}
	pGame->LoopGame();
	//pGame->ClearGame();
	delete pGame;
	return 0;
}



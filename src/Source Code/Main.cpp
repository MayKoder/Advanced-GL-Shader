#include <iostream>
#include "MainGame.h"

#include<ShObjIdl_core.h>


#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#ifdef _DEBUG
//#define TEST_MEMORY_MANAGER
#include "mmgr/mmgr.h"
#endif
#include"Globals.h"

int main(int argc, char** argv) //argument used to call SDL main
{
	MainGame mainGame;
	mainGame.run();

#ifdef _DEBUG
	int leaks = MAX(0, m_getMemoryStatistics().totalAllocUnitCount - 23);
	LOG("With %d memory leaks!\n", (leaks > 0) ? leaks : 0);
#endif

	return 0;
}
// Overriding.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "NPC.h"
#include "Mob.h"

// Common Runtime Debugger
#include <crtdbg.h>

// new Overriding
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CCharacter* haJung = new CMob();
	delete haJung;
	
	getchar();

	return 0;
}


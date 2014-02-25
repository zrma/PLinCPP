// ClassTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <crtdbg.h>
#include "GameManager.h"
#include "WellRandom.h"
#include "UIManager.h"

#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CGameManager::GetInstance()->Run();
	CGameManager::ReleaseInstance();
	CWellRandom::ReleaseInstance();
	CUIManager::ReleaseInstance();
	
	getchar();
	return 0;
}
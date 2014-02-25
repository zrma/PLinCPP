// Game.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <sstream>

bool	MainLoop();
bool	isContinue = false;
CPlayer	player;

int _tmain(int argc, _TCHAR* argv[])
{
	while(MainLoop());

	printf_s("게임을 종료합니다.\n종료하시려면 [엔터]를 누르세요.");
	getchar();

	return 0;
}

bool MainLoop()
{
	std::string					inputString;
	std::string					token;
	std::vector<std::string>	parameterArray;

	// 새 케릭터 생성
	if(!isContinue)
	{
		player.InitialzeCharacter();
		isContinue = true;
	}

	// 스테이터스 프롬프트 출력
	player.DisplayStatus();
	getline(std::cin, inputString);
	
	std::stringstream parsingString(inputString);

	if(inputString == "끝")
		return false;

	while(parsingString >> token)
	{
		parameterArray.push_back(token);
	}

	printf_s("[ ");
	for(auto iter = parameterArray.begin(); iter != parameterArray.end(); ++iter)
	{
		printf_s("%s ", iter->c_str());
	}
	printf_s("]를 입력하셨습니다.\n");

	return true;
}

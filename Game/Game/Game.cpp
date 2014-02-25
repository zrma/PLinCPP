// Game.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	printf_s("������ �����մϴ�.\n�����Ͻ÷��� [����]�� ��������.");
	getchar();

	return 0;
}

bool MainLoop()
{
	std::string					inputString;
	std::string					token;
	std::vector<std::string>	parameterArray;

	// �� �ɸ��� ����
	if(!isContinue)
	{
		player.InitialzeCharacter();
		isContinue = true;
	}

	// �������ͽ� ������Ʈ ���
	player.DisplayStatus();
	getline(std::cin, inputString);
	
	std::stringstream parsingString(inputString);

	if(inputString == "��")
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
	printf_s("]�� �Է��ϼ̽��ϴ�.\n");

	return true;
}

// ClassTest.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Ship.h"
#include "Aircraft.h"
#include "Battleship.h"
#include "Player.h"
#include <iostream>
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	CPlayer user_1;
	int turn = 1;

	printf_s("�ʱ�ȭ �Ϸ�\n");

	user_1.SetPosition();
	
	Position hitPos;
	HitResult hitResult;

	while (user_1.GetLeftShips() > 0)
	{
		printf_s("----------------------------------\n");
		printf_s("[%d��°] ��ǥ�� �Է� �� �ּ��� : ", turn);
		std::cin >> hitPos.x >> hitPos.y;

		++turn;

		// printf_s("\n%c%c\n", input_string.c_str()[0], input_string.c_str()[1]);

		hitResult = user_1.HitCheck(hitPos);
		switch (hitResult)
		{
			case MISS:
				printf_s("Miss!\n");
				break;
			case HIT:
				printf_s("Hit!\n");
				break;
			case DESTORY:
				printf_s("Destroy!\n");
				break;
			default:
				break;
		}
	}

	printf_s("��� �谡 �ı� �Ǿ����ϴ�.\n");

	getchar();

	return 0;
}


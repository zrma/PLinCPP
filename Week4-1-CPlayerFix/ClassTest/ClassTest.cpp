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
	
	user_1.SetPosition();
	printf_s("�ʱ�ȭ �Ϸ�\n");

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
			case DESTROY_AIRCRAFT:
				printf_s("Destroy Aircraft!\n");
				break;
			case DESTROY_BATTLESHIP:
				printf_s("Destroy Battleship!\n");
				break;
			case DESTROY_CRUISER:
				printf_s("Destroy Cruiser!\n");
				break;
			case DESTROY_DESTROYER:
				printf_s("Destroy Destroyer!\n");
				break;
			case DESTROY_SUBMARINE:
				printf_s("Destroy Submarine!\n");
				break;
			default:
				printf_s("Don\'t Print Here!\n");
				break;
		}
	}

	printf_s("��� �谡 �ı� �Ǿ����ϴ�.\n");

	getchar();
	getchar();

	return 0;
}


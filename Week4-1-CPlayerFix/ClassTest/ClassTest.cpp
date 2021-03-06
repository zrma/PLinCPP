// ClassTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	printf_s("초기화 완료\n");

	Position hitPos;
	HitResult hitResult;

	while (user_1.GetLeftShips() > 0)
	{
		printf_s("----------------------------------\n");
		printf_s("[%d턴째] 좌표를 입력 해 주세요 : ", turn);
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

	printf_s("모든 배가 파괴 되었습니다.\n");

	getchar();
	getchar();

	return 0;
}


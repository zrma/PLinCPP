// bs_oop.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include "Aircraft.h"

// 다형성을 이용하여, 
// 다양한 종류의 배 정보를 함수 하나로 출력 가능
void PrintShip(CShip ship)
{
	ship.PrintPosition();
}


int _tmain(int argc, _TCHAR* argv[])
{	
	int errcheck[10] = {0,};					

	printf_s("<------ BattleShip Game START! -------->\n Create By agebreak.\n");

	// Player 객체의 생성
	CPlayer com;
	
	// 배들의 위치 세팅
	com.SetPosition();	


	printf_s("포지션 세팅.... OK!\n");

	int destroyCount = 0;
	std::string inputPos;

	int turn = 0;

	while (destroyCount < 7)
	{
		++turn;

		printf_s("<<현재 턴 : %d>>\n", turn);

		printf_s("공격좌표를 입력해 주세요. (ex. F2, E5..) : ");
		std::cin>>inputPos;

		Position attackPos;
		attackPos.x = inputPos.c_str()[0];
		attackPos.y = inputPos.c_str()[1];

		HitResult result = com.HitCheck(attackPos);
		switch (result)
		{
		case MISS:
			printf_s("%c%c - 안맞았지롱.. 음하하핫~~\n", attackPos.x, attackPos.y);
			break;
		case HIT:
			printf_s("%c%c - 꾸엑~ 히트 했다냥..아프다냥..\n", attackPos.x, attackPos.y);
			break;
		case DESTROY:
			printf_s("%c%c - 우오앙~ 파괴되었다냥~ \n", attackPos.x, attackPos.y);

			// 격추 수를 추가 한다
			++destroyCount;
			break;
		default:
			break;
		}
	}

	printf_s("<------ BattleShip Game END!! -------->\n Create By agebreak.\n");
	printf_s("<< 총 턴 수 : %d", turn);


	getchar();	


	return 0;
}


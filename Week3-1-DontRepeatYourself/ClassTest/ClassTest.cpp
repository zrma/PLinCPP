// ClassTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Ship.h"
#include "Aircraft.h"
#include "Battleship.h"
#include "Player.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CPlayer user_1;

	user_1.SetPosition();
	
	Position hitPos[10];
	hitPos[0].x = 'A';
	hitPos[0].y = '4';
	hitPos[1].x = 'A';
	hitPos[1].y = '5';
	hitPos[2].x = 'A';
	hitPos[2].y = '6';
	hitPos[3].x = 'A';
	hitPos[3].y = '7';
	hitPos[4].x = 'A';
	hitPos[4].y = '8';

	hitPos[5].x = 'B';
	hitPos[5].y = '8';
	hitPos[6].x = 'C';
	hitPos[6].y = '8';
	hitPos[7].x = 'D';
	hitPos[7].y = '8';
	hitPos[8].x = 'E';
	hitPos[8].y = '8';
	hitPos[9].x = 'F';
	hitPos[9].y = '8';

	for(int i = 0; i < 10; i++)
	{
		HitResult hitResult = user_1.HitCheck(hitPos[i]);
		switch (hitResult)
		{
			case MISS:
				printf_s("Miss!\n");
				break;
			case HIT:
				printf_s("Hit!\n");
				break;
			case DESTORY:
				printf_s("Destroy\n");
				break;
			default:
				break;
		}
	}
	getchar();

	return 0;
}


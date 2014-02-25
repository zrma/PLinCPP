// ClassTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Ship.h"
#include "Aircraft.h"
#include "Battleship.h"


int _tmain(int argc, _TCHAR* argv[])
{
	printf_s("CShip 선언\n");
	CShip pShip;

	printf_s("\nnew CShip\n");
	CShip* pShip2 = new CShip();
	printf_s("\nnew CAircraft\n");
	CAircraft* pAircraft2 = new CAircraft();

	printf_s("\ndelete CShip\n");
	delete pShip2;
	printf_s("\nnew CAircraft\n");
	delete pAircraft2;

	printf_s("\n________________\n");

	CAircraft aircraft;
	CBattleship battleship;

	aircraft.AddPosition('A', '5');
	aircraft.AddPosition('B', '5');
	aircraft.AddPosition('C', '5');
	aircraft.AddPosition('D', '5');
	aircraft.AddPosition('E', '5');
	aircraft.AddPosition('F', '5');

	battleship.AddPosition('A', '4');
	battleship.AddPosition('B', '4');
	battleship.AddPosition('C', '4');
	battleship.AddPosition('D', '4');
	battleship.AddPosition('E', '4');

	aircraft.PrintPosition();
	battleship.PrintPosition();

	Position hitPos[10];
	hitPos[0].x = 'A';
	hitPos[0].y = '5';
	hitPos[1].x = 'A';
	hitPos[1].y = '5';
	hitPos[2].x = 'A';
	hitPos[2].y = '5';
	hitPos[3].x = 'A';
	hitPos[3].y = '5';
	hitPos[4].x = 'A';
	hitPos[4].y = '5';

	hitPos[5].x = 'A';
	hitPos[5].y = '5';
	hitPos[6].x = 'B';
	hitPos[6].y = '5';
	hitPos[7].x = 'C';
	hitPos[7].y = '5';
	hitPos[8].x = 'D';
	hitPos[8].y = '5';
	hitPos[9].x = 'E';
	hitPos[9].y = '5';

	for(int i = 0; i < 10; i++)
	{
		HitResult hitResult = aircraft.HitCheck(hitPos[i]);
		switch (hitResult)
		{
			case MISS:
				printf_s("Miss!\n");
				break;
			case HIT:
				printf_s("Hit!\n");
				break;
			case DESTORY:
				printf_s("Destory - %s\n", aircraft.GetName().c_str());
				break;
			default:
				break;
		}
	}
	getchar();

	return 0;
}


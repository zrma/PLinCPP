// Week1-2-BattleShip.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#define MAXSHIP 7

int _tmain(int argc, _TCHAR* argv[])
{
	std::string atkLoc;
	int shipHP[MAXSHIP] = {5, 4, 3, 2, 2, 1, 1};
	int total = MAXSHIP;
	std::string shipName[MAXSHIP] = {"Aircraft", "Battleship", "Cruiser", "Destroyer", "Destroyer", "Submarine", "Submarine"};

	system("cls");
	printf_s("\n\n\n\n");
	while(total)
	{
		for(int i = 0 ; i < MAXSHIP ; ++i)
		{
			printf_s("<%s> : %d\n", shipName[i].c_str(), shipHP[i]);
		}
		printf_s("\n\nWhere Do You Attack (ex : A3) : ");
		std::getline(std::cin, atkLoc);

		system("cls");
		printf_s("\n\n");

		if(atkLoc.length() != 2)
		{
			printf_s("Input Location with 2 length (ex : A3).\n\n");
			continue;
		}

		int num = 0;
		srand((unsigned int) time(NULL));
		num = rand() % 2;
		int rnum = 0;

		switch(num)
		{
			case 0:
				printf_s("Miss! [%s]\n\n", atkLoc.c_str());
				break;
			case 1:
				do{
					rnum = rand() % MAXSHIP;
				}while(shipHP[rnum] == 0);
				
				--shipHP[rnum];
				
				if(shipHP[rnum] == 0)
				{
					printf_s("Destroy %s!!! [%s]\n\n", shipName[rnum].c_str(), atkLoc.c_str());
					--total;
				}
				else
				{
					std::cout << "Hit!! [" << atkLoc.c_str() << "]" << std::endl << std::endl; 
				}
				break;
			default:
				printf_s("error\n\n\n");
				break;
		}
	}

	system("cls");
	printf_s("\n\n\n\n\n\n\n\n\n\n\n\n                                    ");
	printf_s(" YOU WIN!!! ");
	getchar();

	return 0;
}


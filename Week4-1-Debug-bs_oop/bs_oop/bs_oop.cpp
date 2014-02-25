// bs_oop.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include "Aircraft.h"

// �������� �̿��Ͽ�, 
// �پ��� ������ �� ������ �Լ� �ϳ��� ��� ����
void PrintShip(CShip ship)
{
	ship.PrintPosition();
}


int _tmain(int argc, _TCHAR* argv[])
{	
	int errcheck[10] = {0,};					

	printf_s("<------ BattleShip Game START! -------->\n Create By agebreak.\n");

	// Player ��ü�� ����
	CPlayer com;
	
	// ����� ��ġ ����
	com.SetPosition();	


	printf_s("������ ����.... OK!\n");

	int destroyCount = 0;
	std::string inputPos;

	int turn = 0;

	while (destroyCount < 7)
	{
		++turn;

		printf_s("<<���� �� : %d>>\n", turn);

		printf_s("������ǥ�� �Է��� �ּ���. (ex. F2, E5..) : ");
		std::cin>>inputPos;

		Position attackPos;
		attackPos.x = inputPos.c_str()[0];
		attackPos.y = inputPos.c_str()[1];

		HitResult result = com.HitCheck(attackPos);
		switch (result)
		{
		case MISS:
			printf_s("%c%c - �ȸ¾�����.. ��������~~\n", attackPos.x, attackPos.y);
			break;
		case HIT:
			printf_s("%c%c - �ٿ�~ ��Ʈ �ߴٳ�..�����ٳ�..\n", attackPos.x, attackPos.y);
			break;
		case DESTROY:
			printf_s("%c%c - �����~ �ı��Ǿ��ٳ�~ \n", attackPos.x, attackPos.y);

			// ���� ���� �߰� �Ѵ�
			++destroyCount;
			break;
		default:
			break;
		}
	}

	printf_s("<------ BattleShip Game END!! -------->\n Create By agebreak.\n");
	printf_s("<< �� �� �� : %d", turn);


	getchar();	


	return 0;
}


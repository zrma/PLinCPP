#include "stdafx.h"
#include "Player.h"
#include "Aircraft.h"
#include "Battleship.h"
#include "Destroyer.h"
#include "Crusiser.h"
#include "Submarine.h"


CPlayer::CPlayer(void)
{

}

CPlayer::~CPlayer(void)
{
}

void CPlayer::SetPosition()
{
	CAircraft	aircraft;
	CBattleship battleship;
	CCrusiser	cruiser;
	CDestroyer	destroyer_1;
	CDestroyer	destroyer_2;
	CSubmarine	submarine_1;
	CSubmarine	submarine_2;	

	/*
	CAircraft* pAircraft = NULL;
	pAircraft->AddPosition('D', '7');
	*/

	aircraft.AddPosition('D', '7');
	aircraft.AddPosition('E', '7');
	aircraft.AddPosition('F', '7');
	aircraft.AddPosition('G', '7');
	aircraft.AddPosition('H', '7');

	battleship.AddPosition('G', '1');
	battleship.AddPosition('G', '2');
	battleship.AddPosition('G', '3');
	battleship.AddPosition('G', '4');

	cruiser.AddPosition('A', '5');
	cruiser.AddPosition('B', '5');
	cruiser.AddPosition('C', '5');

	destroyer_1.AddPosition('C', '2');
	destroyer_1.AddPosition('C', '3');
	destroyer_2.AddPosition('H', '2');
	destroyer_2.AddPosition('H', '3');

	submarine_1.AddPosition('B', '7');
	submarine_2.AddPosition('E', '3');


	m_Ships[0] = aircraft;
	m_Ships[1] = battleship;
	m_Ships[2] = cruiser;
	m_Ships[3] = destroyer_1;
	m_Ships[4] = destroyer_2;
	m_Ships[5] = submarine_1;
	m_Ships[6] = submarine_2;

	
}

HitResult CPlayer::HitCheck(Position hitPos)
{
	// 자신이 가진 모든 배들이 피격 되었는지를 체크해야 한다.
	// 배의 피격 결과를 반환해야 한다.

	HitResult result;

	int shipCount = sizeof(m_Ships) / sizeof(CShip);

	for(int i = 0; i < shipCount; ++i)
	{		
		result = m_Ships[i].HitCheck(hitPos);

		m_Ships[i].PrintPosition();

		if(result == DESTROY)
		{
			printf_s("%s가 파괴 되었습니다...훗~~ \n", m_Ships[i].GetName().c_str());
		}

		if(result != MISS)
			return result;
	}

	return MISS;





	//HitResult result = MISS;

	//result = m_Aircraft.HitCheck(hitPos);
	//if(result != MISS) 
	//	return result;

	//result = m_Battleship.HitCheck(hitPos);
	//if(result != MISS) 
	//	return result;

	//result = m_Cruiser.HitCheck(hitPos);
	//if(result != MISS) 
	//	return result;

	//result = m_Destroyer_1.HitCheck(hitPos);
	//if(result != MISS) 
	//	return result;

	//result = m_Destroyer_2.HitCheck(hitPos);
	//if(result != MISS) 
	//	return result;

	//result = m_Submarine_1.HitCheck(hitPos);
	//if(result != MISS) 
	//	return result;

	//result = m_Submarine_2.HitCheck(hitPos);
	
	return result;
}



#include "stdafx.h"
#include "Player.h"

// 헤더파일 커플링 제거
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
#include <iostream>

CPlayer::CPlayer(void)
{
	CAircraft	aircraft;
	CBattleship battleship;
	CCruiser	cruiser;
	CDestroyer	destroyer_1;
	CDestroyer	destroyer_2;
	CSubmarine	submarine_1;
	CSubmarine	submarine_2;

	m_Ships[0] = aircraft;
	m_Ships[1] = battleship;
	m_Ships[2] = cruiser;
	m_Ships[3] = destroyer_1;
	m_Ships[4] = destroyer_2;
	m_Ships[5] = submarine_1;
	m_Ships[6] = submarine_2;

	m_LeftShips = sizeof(m_Ships) / sizeof(CShip);
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::SetPosition()
{
	m_Ships[0].AddPosition('B','8');
	m_Ships[0].AddPosition('C','8');
	m_Ships[0].AddPosition('D','8');
	m_Ships[0].AddPosition('E','8');
	m_Ships[0].AddPosition('F','8');

	m_Ships[1].AddPosition('A','4');
	m_Ships[1].AddPosition('A','5');
	m_Ships[1].AddPosition('A','6');
	m_Ships[1].AddPosition('A','7');

	m_Ships[2].AddPosition('F','4');
	m_Ships[2].AddPosition('F','5');
	m_Ships[2].AddPosition('F','6');

	m_Ships[3].AddPosition('H','6');
	m_Ships[3].AddPosition('H','7');

	m_Ships[4].AddPosition('C','1');
	m_Ships[4].AddPosition('C','2');

	m_Ships[5].AddPosition('C','7');

	m_Ships[6].AddPosition('G','5');
}

HitResult CPlayer::HitCheck(Position hitPos)
{
	HitResult tempResult = MISS;

	for (int i = 0; i < sizeof(m_Ships)/sizeof(CShip); i++)
	{
		tempResult = m_Ships[i].HitCheck(hitPos);

		if(tempResult != HIT && tempResult != MISS)
		{
			if(!m_Ships[i].IsDead())
			{
					--m_LeftShips;
					m_Ships[i].SetHPMAX(0);
			}
		}
		if(tempResult != MISS)
			return tempResult;
	}
	
	return tempResult;
}
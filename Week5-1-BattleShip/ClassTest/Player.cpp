#include "stdafx.h"
#include "Player.h"

// 헤더파일 커플링 제거
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
#include <iostream>
#include <time.h>

CPlayer::CPlayer(void)
{
	CAircraft*		pAircraft	= new CAircraft();
	CBattleship*	pBattleship	= new CBattleship();
	CCruiser*		pCruiser		= new CCruiser();
	CDestroyer*		pDestroyer_1	= new CDestroyer();
	CDestroyer*		pDestroyer_2	= new CDestroyer();
	CSubmarine*		pSubmarine_1	= new CSubmarine();
	CSubmarine*		pSubmarine_2	= new CSubmarine();

	m_Ships[0] = pAircraft;
	m_Ships[1] = pBattleship;
	m_Ships[2] = pCruiser;
	m_Ships[3] = pDestroyer_1;
	m_Ships[4] = pDestroyer_2;
	m_Ships[5] = pSubmarine_1;
	m_Ships[6] = pSubmarine_2;

	m_LeftShips = sizeof(m_Ships) / sizeof(CShip*);
	m_MyMap.InitMapInfo();
}

CPlayer::~CPlayer(void)
{
	for(int i = 0; i < sizeof(m_Ships) / sizeof(CShip*); ++i)
	{
		if(m_Ships[i])
		{
			delete(m_Ships[i]);
			m_Ships[i] = NULL;
		}
	}
}

void CPlayer::SetPosition()
{

	m_Ships[0]->AddPosition('B','8');
	m_Ships[0]->AddPosition('C','8');
	m_Ships[0]->AddPosition('D','8');
	m_Ships[0]->AddPosition('E','8');
	m_Ships[0]->AddPosition('F','8');

	m_Ships[1]->AddPosition('A','4');
	m_Ships[1]->AddPosition('A','5');
	m_Ships[1]->AddPosition('A','6');
	m_Ships[1]->AddPosition('A','7');

	m_Ships[2]->AddPosition('F','4');
	m_Ships[2]->AddPosition('F','5');
	m_Ships[2]->AddPosition('F','6');

	m_Ships[3]->AddPosition('H','6');
	m_Ships[3]->AddPosition('H','7');

	m_Ships[4]->AddPosition('C','1');
	m_Ships[4]->AddPosition('C','2');

	m_Ships[5]->AddPosition('C','7');

	m_Ships[6]->AddPosition('G','5');

}

HitResult CPlayer::HitCheck(Position hitPos)
{
	HitResult tempResult = MISS;

	for (int i = 0; i < sizeof(m_Ships)/sizeof(CShip*); i++)
	{
		tempResult = m_Ships[i]->HitCheck(hitPos);

		if(tempResult != HIT && tempResult != MISS)
		{
			if(!m_Ships[i]->IsDead())
			{
				--m_LeftShips;
				m_Ships[i]->SetHPMAX(0);
			}
		}
		if(tempResult != MISS)
			return tempResult;
	}

	return tempResult;
}

void CPlayer::SetPositionRandom()
{
	int nPosX, nPosY;
	VerticalType isVertical = VERTICAL;
	bool isValid;

	int nPositionedShip = 0;
	int shipSize = 0;

	srand((int) time(NULL));

	while(nPositionedShip < m_LeftShips)
	{
		isValid = true;
		shipSize = m_Ships[nPositionedShip]->GetHPMAX();
		nPosX = rand() % MAP_SIZE;
		nPosY = rand() % MAP_SIZE;
		(rand() % 2 == 0) ? isVertical = VERTICAL : isVertical = HORIZON; 

		switch (isVertical)
		{
		case VERTICAL:
			for(int i = 0; i < shipSize; ++i)
			{
				if(m_MyMap.GetMapInfo(nPosX + i, nPosY) != WATER)
				{
					isValid = false;
					continue;
				}
			}
			break;
		case HORIZON:
			for(int i = 0; i < shipSize; ++i)
			{
				if(m_MyMap.GetMapInfo(nPosX, nPosY + i) != WATER)
				{
					isValid = false;
					continue;
				}
			}
			break;
		default:
			printf_s("Don't Reach Here \n");
			break;
		}

		if(isValid == false)
			continue;

		switch (isVertical)
		{
		case VERTICAL:
			for(int i = 0; i < shipSize; ++i)
			{
				m_MyMap.SetMapInfo(nPosX + i, nPosY, m_Ships[nPositionedShip]->GetType());
				m_Ships[nPositionedShip]->AddPosition((char)(nPosX + i + 'A'), (char) (nPosY + '1'));
			}
			break;
		case HORIZON:
			for(int i = 0; i < shipSize; ++i)
			{
				m_MyMap.SetMapInfo(nPosX, nPosY + i, m_Ships[nPositionedShip]->GetType());
				m_Ships[nPositionedShip]->AddPosition((char)(nPosX + 'A'), (char) (nPosY + '1' + i));
			}
			break;
		default:
			printf_s("Don't Reach Here \n");
			break;
		}

		++nPositionedShip;
	}
}

#include "stdafx.h"
#include "Player.h"
#include <iostream>


CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::SetPosition()
{
	m_Aircraft.AddPosition('B','8');
	m_Aircraft.AddPosition('C','8');
	m_Aircraft.AddPosition('D','8');
	m_Aircraft.AddPosition('E','8');
	m_Aircraft.AddPosition('F','8');

	m_Battleship.AddPosition('A','4');
	m_Battleship.AddPosition('A','5');
	m_Battleship.AddPosition('A','6');
	m_Battleship.AddPosition('A','7');

	m_Cruiser.AddPosition('F','4');
	m_Cruiser.AddPosition('F','5');
	m_Cruiser.AddPosition('F','6');

	m_Destroyer_1.AddPosition('H','6');
	m_Destroyer_1.AddPosition('H','7');

	m_Destroyer_2.AddPosition('C','1');
	m_Destroyer_2.AddPosition('C','2');

	m_Submarine_1.AddPosition('C','7');

	m_Submarine_2.AddPosition('G','5');
}

HitResult CPlayer::HitCheck(Position hitPos)
{
	HitResult tempResult = m_Aircraft.HitCheck(hitPos);
	if(tempResult != MISS){
		return tempResult;
	}

	tempResult = m_Battleship.HitCheck(hitPos);
	if(tempResult != MISS){
		return tempResult;
	}

	tempResult = m_Cruiser.HitCheck(hitPos);
	if(tempResult != MISS){
		return tempResult;
	}

	tempResult = m_Destroyer_1.HitCheck(hitPos);
	if(tempResult != MISS){
		return tempResult;
	}

	tempResult = m_Destroyer_2.HitCheck(hitPos);
	if(tempResult != MISS){
		return tempResult;
	}

	tempResult = m_Submarine_1.HitCheck(hitPos);
	if(tempResult != MISS){
		return tempResult;
	}

	tempResult = m_Submarine_2.HitCheck(hitPos);

	return tempResult;
}
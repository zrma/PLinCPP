#include "stdafx.h"
#include "Battleship.h"


CBattleship::CBattleship(void)
{
	m_Name	= "BattleShip";
	m_HPMAX	= 4;
	m_Type	= BATTLESHIP;
}


CBattleship::~CBattleship(void)
{
}

HitResult CBattleship::HitCheck( Position hitPos )
{
	HitResult result = CShip::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_BATTLESHIP : result;
}

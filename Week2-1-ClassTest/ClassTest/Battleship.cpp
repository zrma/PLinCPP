#include "stdafx.h"
#include "Battleship.h"


CBattleship::CBattleship(void)
{
	printf_s("Create CBattleShip!\n");

	m_Name	= "BattleShip";
	m_HPMAX	= 4;
	m_Type	= BATTLESHIP;
}


CBattleship::~CBattleship(void)
{
	printf_s("Destroy CBattleShip!\n");
}

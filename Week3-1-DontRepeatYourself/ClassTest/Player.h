#pragma once
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void		SetPosition();
	HitResult	HitCheck(Position hitPos);

private:
	CAircraft	m_Aircraft;
	CBattleship	m_Battleship;
	CCruiser	m_Cruiser;
	CDestroyer	m_Destroyer_1; 
	CDestroyer	m_Destroyer_2;
	CSubmarine	m_Submarine_1;
	CSubmarine	m_Submarine_2;
};


#pragma once

#include "Ship.h"
#include "BattleShipMap.h"
/*
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
*/

enum VerticalType
{
	VERTICAL,
	HORIZON
};

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void		SetPosition();
	void		SetPositionRandom();
	int			GetLeftShips() { return m_LeftShips; }
	HitResult	HitCheck(Position hitPos);

public:
	CBattleShipMap	m_MyMap;

private:
	CShip*		m_Ships[7];
	int			m_LeftShips;
};


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

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void		SetPosition();
	void		SetPositionRandom();
	HitResult	HitCheck(Position hitPos);

	int			StartAttack(CPlayer* defender);
	void		GuessShipStatus( Position pos, int size );
	void		GuessBlankStatus();

public:
	CBattleShipMap	m_MyMap;

private:
	CShip*		m_Ships[6];
	int			m_LeftShips;
};


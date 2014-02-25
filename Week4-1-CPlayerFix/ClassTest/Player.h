#pragma once

#include "Ship.h"
/*
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
*/

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void		SetPosition();
	int			GetLeftShips() { return m_LeftShips; }
	HitResult	HitCheck(Position hitPos);

private:
	CShip		m_Ships[7];
	int			m_LeftShips;
};


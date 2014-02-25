#pragma once

#include "Ship.h"
#include "BattleShipMap.h"

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

	void			SetPositionRandom();
	int				StartAttack(CPlayer* defender);

private:
	HitResult	HitCheck(Position hitPos);

	void			InitGuessShipState();
	void			GuessDestroyedShip(HitResult result, Position pos);

	void			CalculateProbability();
	Position		GetBestPosition();

	int				GetProbabilityThisPosition(Position pos);
	int				GetProbabilitySurroundShip(Position pos, int shipSize);
	
private:
	CBattleShipMap
		m_MyMap;

	CShip*		m_Ships[6];
	int				m_LeftShips;
};


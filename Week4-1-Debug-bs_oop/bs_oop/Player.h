#pragma once
#include "Ship.h"
/*
#include "Aircraft.h"
#include "Battleship.h"
#include "Destroyer.h"
#include "Crusiser.h"
#include "Submarine.h"
*/

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void SetPosition();	// 배의 위치들을 배치한다
	HitResult HitCheck(Position hitPos);	// 피격 체크
	bool IsLive();

	CShip GetShip(int index) { return m_Ships[index]; }


protected:
	/*
	CAircraft	m_Aircraft;
	CBattleship m_Battleship;
	CCrusiser	m_Cruiser;
	CDestroyer	m_Destroyer_1;
	CDestroyer	m_Destroyer_2;
	CSubmarine	m_Submarine_1;
	CSubmarine	m_Submarine_2;
	*/

	CShip		m_Ships[7];	

};


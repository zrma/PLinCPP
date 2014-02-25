#pragma once
#include <string>

// 히트 결과
enum HitResult
{
	MISS,
	HIT,
	DESTROY,

	DESTROY_AIRCRAFT,
	DESTROY_BATTLESHIP,
	DESTROY_CRUISER,
	DESTROY_DESTROYER,
	DESTROY_SUBMARINE,
};

enum ShipType
{
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,
	SUBMARINE,

};

struct Position
{
	char x;	// x좌표
	char y;	// y좌표
	bool bHit;

};

class CShip
{
public:
	CShip(void);
	virtual ~CShip(void);

	void		AddPosition(char x, char y);
	HitResult	HitCheck(Position pos);	
	void		PrintPosition();	

	// 현재 HP를 반환한다.
	int GetHP() {return m_HP;}
	std::string GetName() {return m_Name;}
	

protected:
	std::string m_Name;
	ShipType m_Type;
	int m_HP;
	Position m_Pos[5];

	int m_positionIndex;
};

#pragma once
#include <string>

// 히트 결과
enum HitResult
{
	MISS,
	HIT,
	DESTORY,
};

// 배 종류
enum ShipType
{
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,
	SUBMARINE,
};

class Position
{
public:
	char	x;		// x 좌표
	char	y;		// y 좌표
	bool	bHit;	// 히트 여부 체크
};

class CShip
{
public:
	CShip(void);
	virtual	~CShip(void);

	void		AddPosition(char x, char y);
	void		PrintPosition();
	HitResult	HitCheck(Position hitPos);

	// 멤버변수 접근메소드
	std::string	GetName() { return m_Name; }
	int			GetHPMAX() { return m_HPMAX; }
	int			GetHPCURRENT() { return m_HPCurrent; }
	int			GetType() { return m_Type; }

protected:
	// 멤버변수
	int			m_HPMAX;
	int			m_HPCurrent;
	std::string	m_Name;
	ShipType	m_Type;
	Position	m_Pos[5];
};

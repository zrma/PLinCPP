#pragma once
#include <string>

// ��Ʈ ���
enum HitResult
{
	MISS,
	HIT,
	DESTROY,

	DESTROY_AIRCRAFT,
	DESTROY_BATTLESHIP,
	DESTROY_CRUISER,
	DESTROY_DESTROYER,
	DESTROY_SUBMARINE
};

// �� ����
enum ShipType
{
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,
	SUBMARINE,
	FOG,
	WATER,
	NONE
};

class Position
{
public:
	char	x;		// x ��ǥ
	char	y;		// y ��ǥ
	bool	bHit;	// ��Ʈ ���� üũ
};

class CShip
{
public:
	CShip(void);
	virtual	~CShip(void);

	void		AddPosition(char x, char y);
	void		PrintPosition();

	virtual		HitResult	HitCheck(Position hitPos);

	// ������� ���ٸ޼ҵ�
	std::string	GetName() { return m_Name; }
	void		SetHPMAX( int hp ) { m_HPMAX = hp; }
	bool		IsDead() { return (m_HPMAX == 0) ? true : false; }
	int			GetHPMAX() { return m_HPMAX; }
	int			GetHPCURRENT() { return m_HPCurrent; }
	ShipType	GetType() { return m_Type; }

protected:
	// �������
	int			m_HPMAX;
	int			m_HPCurrent;
	std::string	m_Name;
	ShipType	m_Type;
	Position	m_Pos[5];
};

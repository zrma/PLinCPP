#pragma once
#include <string>

// ��Ʈ ���
enum HitResult
{
	MISS,
	HIT,
	DESTORY,
};

// �� ����
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
	HitResult	HitCheck(Position hitPos);

	// ������� ���ٸ޼ҵ�
	std::string	GetName() { return m_Name; }
	int			GetHPMAX() { return m_HPMAX; }
	int			GetHPCURRENT() { return m_HPCurrent; }
	int			GetType() { return m_Type; }

protected:
	// �������
	int			m_HPMAX;
	int			m_HPCurrent;
	std::string	m_Name;
	ShipType	m_Type;
	Position	m_Pos[5];
};
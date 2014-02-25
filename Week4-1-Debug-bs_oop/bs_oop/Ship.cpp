#include "stdafx.h"
#include "Ship.h"
#include <string.h>


CShip::CShip(void)
{
	//printf_s("Create CShip!\n");
	m_HP = 0;
	memset(m_Pos, 0, sizeof(Position) * 5);
	m_positionIndex = 0;
}


CShip::~CShip(void)
{
	//printf_s("Destroy CShip!!\n");
}

void CShip::AddPosition(char x, char y)
{
	// �Է� ���� x,y������ �� ��ġ�� ��ġ�Ѵ�.
	// m_pos[5]�� ���������� �ִ´�.

	// 1. ����ü �����
	Position pos;
	pos.x = x;
	pos.y = y;
	pos.bHit = false;
	
	m_Pos[m_positionIndex] = pos;
	++m_positionIndex;

}

HitResult CShip::HitCheck(Position pos)
{
	// �迭�� ���� ���
	int count = sizeof(m_Pos) / sizeof(Position);

	for(int i = 0; i < count; ++i)
	{
		// ��Ʈ�� ��� üũ
		if(m_Pos[i].x == pos.x && m_Pos[i].y == pos.y)
		{
			if(m_Pos[i].bHit)
				return HIT;

			m_Pos[i].bHit = true;
			--m_HP;	// HP�� ����

			// HP�� 0�̸� �ı�, �ƴϸ� ��Ʈ
			return (m_HP <= 0) ? DESTROY : HIT;			
		}
	}

	return MISS;
}

void CShip::PrintPosition()
{
	printf_s("Ship Name : %s\n", m_Name.c_str());
}


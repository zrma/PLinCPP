#include "stdafx.h"
#include "Ship.h"
#include <string.h>


CShip::CShip(void)
{
	m_HPMAX	= 0;
	m_HPCurrent = 0;

	memset(m_Pos, 0, sizeof(Position) * 5);
}


CShip::~CShip(void)
{
}

void CShip::AddPosition(char x, char y)
{
	// �Է� ���� x, y������ �� ��ġ�� ��ġ�Ѵ�.
	// m_Pos[5]�� ���������� �ִ´�.
	if(m_HPCurrent < m_HPMAX)
	{
		Position pos;
		pos.x = x;
		pos.y = y;
		pos.bHit = false;

		m_Pos[m_HPCurrent] = pos;	
		++m_HPCurrent;

		//printf_s("%s Position Add %d\n", m_Name.c_str(), m_HPCurrent);
	}
	else
	{
		//printf_s("%s Full\n", m_Name.c_str());
	}
}

HitResult CShip::HitCheck(Position hitPos)
{
	// �Է� ���� ������ ���� �ڱⰡ �¾Ҵ��� �ǰ� ����� ��ȯ�Ѵ�.
	// �Է� ���� ���� �����ǿ� ���� �� ���� ���Ͽ� ����� ��ȯ�Ѵ�.
	// ��Ʈ�ϸ� HPCURRENT�� 1 ��´�.
	// HPCURRENT�� 0�� �Ǹ� �ı� �Ǿ��ٰ� ��ȯ�Ѵ�.

	int arraySize = sizeof(m_Pos) / sizeof(m_Pos[0]);

	for(int i = 0; i < arraySize; i++)
	{
		if(m_Pos[i].x == hitPos.x && m_Pos[i].y == hitPos.y)
		{
			if(m_Pos[i].bHit == false)
			{
				m_Pos[i].bHit = true;
					--m_HPCurrent;
				// printf_s("HP decrease\n");
			}

			return (IsDead()) ? DESTROY : HIT;
		}
	}

	return MISS;
}
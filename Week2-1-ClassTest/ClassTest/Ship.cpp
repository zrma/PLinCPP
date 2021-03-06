#include "stdafx.h"
#include "Ship.h"
#include <string.h>


CShip::CShip(void)
{
	printf_s("Create CShip!\n");

	m_HPMAX	= 0;
	m_HPCurrent = 0;

	memset(m_Pos, 0, sizeof(Position) * 5);
}


CShip::~CShip(void)
{
	printf_s("Destroy CShip!\n");
}

void CShip::AddPosition(char x, char y)
{
	// 입력 받은 x, y값으로 배 위치를 배치한다.
	// m_Pos[5]에 순차적으로 넣는다.
	if(m_HPCurrent < m_HPMAX)
	{
		Position pos;
		pos.x = x;
		pos.y = y;
		pos.bHit = false;

		m_Pos[m_HPCurrent] = pos;	
		++m_HPCurrent;

		printf_s("%s Position Add %d\n", m_Name.c_str(), m_HPCurrent);
	}
	else
	{
		printf_s("%s Full\n", m_Name.c_str());
	}
}

void CShip::PrintPosition()
{
	for(int i = 0; i < m_HPCurrent; i++)
	{
		printf_s("%s Position[%d] - %c%c\n", m_Name.c_str(), i, m_Pos[i].x, m_Pos[i].y);
	}
}

HitResult CShip::HitCheck(Position hitPos)
{
	// 입력 받은 포지션 값에 자기가 맞았는지 피격 결과를 반환한다.
	// 입력 받은 값과 포지션에 저장 된 값을 비교하여 결과를 반환한다.
	// 히트하면 HPCURRENT를 1 깎는다.
	// HPCURRENT가 0이 되면 파괴 되었다고 반환한다.

	int arraySize = sizeof(m_Pos) / sizeof(m_Pos[0]);
	// arraySize = m_HPMAX;

	for(int i = 0; i < arraySize; i++)
	{
		if(m_Pos[i].x == hitPos.x && m_Pos[i].y == hitPos.y)
		{
			if(m_Pos[i].bHit == false)
			{
				m_Pos[i].bHit = true;
				--m_HPCurrent;
				printf_s("HP decrease\n");
			}

			return (m_HPCurrent <= 0) ? DESTORY : HIT;
		}
	}

	return MISS;
}
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
	// 입력 받은 x,y값으로 배 위치를 배치한다.
	// m_pos[5]에 순차적으로 넣는다.

	// 1. 구조체 만든다
	Position pos;
	pos.x = x;
	pos.y = y;
	pos.bHit = false;
	
	m_Pos[m_positionIndex] = pos;
	++m_positionIndex;

}

HitResult CShip::HitCheck(Position pos)
{
	// 배열의 갯수 계산
	int count = sizeof(m_Pos) / sizeof(Position);

	for(int i = 0; i < count; ++i)
	{
		// 히트한 경우 체크
		if(m_Pos[i].x == pos.x && m_Pos[i].y == pos.y)
		{
			if(m_Pos[i].bHit)
				return HIT;

			m_Pos[i].bHit = true;
			--m_HP;	// HP를 감소

			// HP가 0이면 파괴, 아니면 히트
			return (m_HP <= 0) ? DESTROY : HIT;			
		}
	}

	return MISS;
}

void CShip::PrintPosition()
{
	printf_s("Ship Name : %s\n", m_Name.c_str());
}


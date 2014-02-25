#include "stdafx.h"
#include "BattleShipMap.h"

CBattleShipMap::CBattleShipMap(void)
{
}


CBattleShipMap::~CBattleShipMap(void)
{
}


void CBattleShipMap::InitMapInfo()
{
	for(int i = 0; i < MAP_SIZE; ++i)
		for(int j = 0; j < MAP_SIZE; ++j)
			m_MapInfo[i][j] = WATER;
}

bool CBattleShipMap::IsValid( Position pos )
{
	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	// 방어 코드
	// 이렇게 체크하지 않으면, 메모리 침범(오버 플로우) 발생 가능성이 있다.
	if(nPosX < 0 || nPosX >= MAP_SIZE || nPosY < 0 || nPosY >= MAP_SIZE)
		return false;

	return true;
}

bool CBattleShipMap::IsValid( char cPosX, char cPosY )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return IsValid(pos);
}

bool CBattleShipMap::SetMapInfo( Position pos, ShipType shipType )
{
	if(!IsValid(pos))
		false;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	if(shipType > 1000)
	{
		printf_s("잠깐 에러 : %d \n", shipType);
		getchar();
	}
	m_MapInfo[nPosX][nPosY] = shipType;

	return true;
}

bool CBattleShipMap::SetMapInfo( char cPosX, char cPosY, ShipType shipType )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return SetMapInfo(pos, shipType);
}

ShipType CBattleShipMap::GetMapInfo( Position pos )
{
	if(!IsValid(pos))
		return NONE;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	return m_MapInfo[nPosX][nPosY];
}

ShipType CBattleShipMap::GetMapInfo( char cPosX, char cPosY )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return GetMapInfo(pos);
}

void CBattleShipMap::DisplayMap()
{
	char	mapLabel[MAX_LABEL] = { 'A', 'B', 'C', 'D', 'S', 'W', 'X', ' ' };
	char	lineLabel[MAP_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

	printf_s("Test Print \n");
	printf_s("____________________________ \n");
	printf_s("     1  2  3  4  5  6  7  8  \n");
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		printf_s("[%c] ", lineLabel[i]);
		for(int j = 0; j < MAP_SIZE; ++j)
			printf_s("[%c]", mapLabel[GetMapInfo(i + 'A', j + '1')]);
		printf_s("\n");
	}
}

void CBattleShipMap::AddCount( Position pos )
{
	if(!IsValid(pos))
		return;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	++m_CountHistory[nPosX][nPosY];
}

void CBattleShipMap::AddCount( char cPosX, char cPosY )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	AddCount(pos);
}

void CBattleShipMap::DisplayCount()
{
	char	lineLabel[MAP_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

	printf_s("Simulating Counting\n");
	printf_s("______________________________________________________ \n");
	printf_s("        1     2     3     4     5     6     7     8    \n");
	printf_s("______________________________________________________ \n\n");

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		printf_s("[%c] | ", lineLabel[i]);
		for(int j = 0; j < MAP_SIZE; ++j)
			printf_s("[%4d]", GetCount(i + 'A', j + '1'));
		printf_s("\n\n");
	}

}

void CBattleShipMap::ResetCount()
{
	memset(m_CountHistory, 0, sizeof(int) * (MAP_SIZE * MAP_SIZE));
}

int CBattleShipMap::GetCount(Position pos)
{
	if(!IsValid(pos))
		return -1;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	return m_CountHistory[nPosX][nPosY];
}

int CBattleShipMap::GetCount( char cPosX, char cPosY )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return GetCount(pos);
}

void CBattleShipMap::SetProbability( Position pos, int turn )
{
	if(!IsValid(pos))
		return;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';
	Position bestPos;

	if(m_Probability[nPosX][nPosY] < 0 && turn != -150)
		return;

	if(turn == 0)
	{
		bestPos = GetBestProbability();
		turn = GetProbability(bestPos);
	}
	
	if(turn < 0 && turn > -50)
		turn = -turn;

	if(turn < -50 && turn > -100)
		turn = 100 + turn;

	if(turn > 600)
		turn = 600;

	m_Probability[nPosX][nPosY] = turn;
}

void CBattleShipMap::SetProbability( char cPosX, char cPosY, int turn )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	SetProbability(pos, turn);
}

void CBattleShipMap::SetProbability( char cPosX, char cPosY, double turn )
{
	SetProbability( cPosX, cPosY, (int) turn );
}

int CBattleShipMap::GetProbability( Position pos )
{
	if(!IsValid(pos))
		return -50;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	return m_Probability[nPosX][nPosY];
}

int CBattleShipMap::GetProbability( char cPosX, char cPosY )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return GetProbability(pos);
}

void CBattleShipMap::DisplayProbability()
{
	char	lineLabel[MAP_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

	printf_s("Simulating Probability\n");
	printf_s("______________________________________________________ \n");
	printf_s("        1     2     3     4     5     6     7     8    \n");
	printf_s("______________________________________________________ \n\n");

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		printf_s("[%c] | ", lineLabel[i]);
		for(int j = 0; j < MAP_SIZE; ++j)

			if(GetProbability(i + 'A', j + '1') == -50){
				printf_s("[    ]");
			}
			else if(GetProbability(i + 'A', j + '1') == -100)
			{
				printf_s("[ ** ]");
			}
			else if(GetProbability(i + 'A', j + '1') == -150)
			{
				printf_s("[====]");
			}
			else
				printf_s("[%4d]", GetProbability(i + 'A', j + '1'));
		printf_s("\n\n");
	}

}

void CBattleShipMap::InitProbability()
{
	memset(m_Probability, 0, sizeof(int) * (MAP_SIZE * MAP_SIZE));
}

Position CBattleShipMap::GetBestProbability()
{
	Position	bestPosition = { NULL, NULL, false };
	int			bestValue = 0;

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		for(int j = 0; j < MAP_SIZE; ++j)
		{
			if(bestValue < m_Probability[i][j])
			{
				bestValue = m_Probability[i][j];
				bestPosition.x = i + 'A';
				bestPosition.y = j + '1';
			}
		}
	}

	return bestPosition;
}

int CBattleShipMap::GetWorstProbabilityValue()
{
	int			worstValue = 1000;

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		for(int j = 0; j < MAP_SIZE; ++j)
		{
			if(worstValue > m_Probability[i][j] && m_Probability[i][j] > 0)
			{
				worstValue = m_Probability[i][j];
			}
		}
	}

	return worstValue;
}


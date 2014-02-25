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
		{
			m_mapInfo[i][j] = WATER;
		}
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

bool CBattleShipMap::SetMapInfo( Position pos, ShipType shipType )
{
	if(!IsValid(pos))
		false;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	m_mapInfo[nPosX][nPosY] = shipType;

	return true;
}

bool CBattleShipMap::SetMapInfo( int nPosX, int nPosY, ShipType shipType )
{
	Position pos;
	pos.x = (char) (nPosX + 'A');
	pos.y = (char) (nPosY + '1');

	return SetMapInfo(pos, shipType);
}

ShipType CBattleShipMap::GetMapInfo( Position pos )
{
	if(!IsValid(pos))
		return NONE;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	return m_mapInfo[nPosX][nPosY];
}

ShipType CBattleShipMap::GetMapInfo( int nPosX, int nPosY )
{
	Position pos;
	pos.x = (char) (nPosX + 'A');
	pos.y = (char) (nPosY + '1');

	return GetMapInfo(pos);
}

void CBattleShipMap::DisplayMap()
{
	char	mapLabel[8] = { 'A', 'B', 'C', 'D', 'S', 'F', 'W', ' ' };
	char	lineLabel[MAP_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

	printf_s("Test Print \n");
	printf_s("____________________________ \n");
	printf_s("     1  2  3  4  5  6  7  8  \n");
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		printf_s("[%c] ", lineLabel[i]);
		for(int j = 0; j < MAP_SIZE; ++j)
			printf_s("[%c]", mapLabel[GetMapInfo(i, j)]);
		printf_s("\n");
	}
}

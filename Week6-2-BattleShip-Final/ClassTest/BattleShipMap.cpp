#include "stdafx.h"
#include "BattleShipMap.h"
#include "UIManager.h"

CBattleShipMap::CBattleShipMap(void)
{
}


CBattleShipMap::~CBattleShipMap(void)
{
}

void CBattleShipMap::InitMapInfo( MapInfoType type )
{
	for(int i = 0; i < MAP_SIZE; ++i)
		for(int j = 0; j < MAP_SIZE; ++j)
			switch (type)
			{
			case MI_ShipType:
				m_MapInfo[i][j] = WATER;
				break;
			case MI_HitResult:
				m_HitResultMap[i][j] = UNKNOWN;
				break;
			case MI_Probability:
				m_ProbabilityMap[i][j] = 0;
				break;
			case MI_All:
				m_MapInfo[i][j] = WATER;
				m_HitResultMap[i][j] = UNKNOWN;
				m_ProbabilityMap[i][j] = 0;
				break;
			default:
				break;
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

bool CBattleShipMap::IsValid( char cPosX, char cPosY )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return IsValid(pos);
}

bool CBattleShipMap::SetMapInfo( Position pos, MapInfo mapInfo )
{
	if(!IsValid(pos))
		return false;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	switch (mapInfo.type)
	{
	case MI_ShipType:
		m_MapInfo[nPosX][nPosY] = mapInfo.value.shipType;
		break;
	case MI_HitResult:
		m_HitResultMap[nPosX][nPosY] = mapInfo.value.hitResult;
		break;
	case MI_Probability:
		m_ProbabilityMap[nPosX][nPosY] = mapInfo.value.probability;
		break;
	default:
		break;
	}

	return true;
}

bool CBattleShipMap::SetMapInfo( char cPosX, char cPosY, MapInfo mapInfo )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return SetMapInfo(pos, mapInfo);
}

MapInfo CBattleShipMap::GetMapInfo( Position pos, MapInfoType type )
{
	MapInfo mapInfo;
	mapInfo.type = type;

	if(!IsValid(pos))
		return mapInfo;

	int nPosX = pos.x - 'A';
	int nPosY = pos.y - '1';

	switch (type)
	{
	case MI_ShipType:
		mapInfo.value.shipType = m_MapInfo[nPosX][nPosY];
		break;
	case MI_HitResult:
		mapInfo.value.hitResult = m_HitResultMap[nPosX][nPosY];
		break;
	case MI_Probability:
		mapInfo.value.probability = m_ProbabilityMap[nPosX][nPosY];
		break;
	default:
		break;
	}

	return mapInfo;
}

MapInfo CBattleShipMap::GetMapInfo( char cPosX, char cPosY, MapInfoType type )
{
	Position pos;
	pos.x = cPosX;
	pos.y = cPosY;

	return GetMapInfo(pos, type);
}

void CBattleShipMap::DisplayMap( MapInfoType type, char cPosX, char cPosY )
{
	char	mapLabel[MAX_LABEL] = { 'A', 'B', 'C', 'D', 'S', 'W', 'X', 'N' };
	char	lineLabel[MAP_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char	string[255] = {0, };

	switch (type)
	{
	case MI_ShipType:
		sprintf_s(string, "    Ship Location Map");
		break;
	case MI_HitResult:
		sprintf_s(string, "    Hit Result Map");
		break;
	case MI_Probability:
		sprintf_s(string, "    Probability Map");
		break;
	default:
		break;
	}
	CUIManager::GetInstance()->BroadCast(string);

	sprintf_s(string, "    -------------------------------------------");
	CUIManager::GetInstance()->BroadCast(string);
	sprintf_s(string, "         1    2    3    4    5    6    7    8  ");
	CUIManager::GetInstance()->BroadCast(string);

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		sprintf_s(string, "    [%c] ", lineLabel[i]);
		CUIManager::GetInstance()->BroadCast(string, false);

		for(int j = 0; j < MAP_SIZE; ++j)
		{
			switch (type)
			{
			case MI_ShipType:

				sprintf_s(string, "[ %c]", mapLabel[m_MapInfo[i][j]]);
				if(m_MapInfo[i][j] != WATER)
					CUIManager::GetInstance()->BroadCast(string, false, 5);
				else
					CUIManager::GetInstance()->BroadCast(string, false);

				break;
			case MI_HitResult:

				if(m_HitResultMap[i][j] == MISS)
				{	
					sprintf_s(string, "MISS");
					CUIManager::GetInstance()->BroadCast(string, false, 1);
				}
				else if(m_HitResultMap[i][j] == HIT)
				{
					sprintf_s(string, "HIT!");
					CUIManager::GetInstance()->BroadCast(string, false, 2);
				}
				else if(m_HitResultMap[i][j] == DESTROY)
				{
					sprintf_s(string, "XXX!");
					CUIManager::GetInstance()->BroadCast(string, false, 3);
				}
				else
				{
					sprintf_s(string, "????");
					CUIManager::GetInstance()->BroadCast(string, false);
				}

				break;
			case MI_Probability:

				sprintf_s(string, "%04d", m_ProbabilityMap[i][j]);

				if(cPosX - 'A' == i && cPosY - '1' == j)
					CUIManager::GetInstance()->BroadCast(string, false, 6);
				else if(m_HitResultMap[i][j] == MISS)
					CUIManager::GetInstance()->BroadCast(string, false, 1);
				else if(m_HitResultMap[i][j] == HIT)
					CUIManager::GetInstance()->BroadCast(string, false, 2);
				else if(m_HitResultMap[i][j] == DESTROY)
					CUIManager::GetInstance()->BroadCast(string, false, 3);
				else
					CUIManager::GetInstance()->BroadCast(string, false);

				break;
			default:
				break;
			}
			sprintf_s(string, " ");
			CUIManager::GetInstance()->BroadCast(string, false);
		}
		sprintf_s(string, " ");
		CUIManager::GetInstance()->BroadCast(string);
	}

	sprintf_s(string, "    -------------------------------------------");
	CUIManager::GetInstance()->BroadCast(string);
}

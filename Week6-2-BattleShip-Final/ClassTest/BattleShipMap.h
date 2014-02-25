#pragma once
#include "Ship.h"

#define MAP_SIZE			8
#define MAX_LABEL		8

enum MapInfoType
{
	MI_NULL,
	MI_ShipType,
	MI_HitResult,
	MI_Probability,
	MI_All
};

union MapValue
{
	int				nValue;
	ShipType	shipType;
	HitResult	hitResult;
	int				probability;
};

class MapInfo
{
public:
	MapInfo()
	{
		Init();
	}
	~MapInfo() {}

	void					Init()
	{
		type = MI_NULL; 
		value.nValue = 0; 
	}

	MapInfoType		type;
	MapValue			value;
};

class CBattleShipMap
{
public:
	CBattleShipMap(void);
	~CBattleShipMap(void);

public:
	bool			IsValid(char cPosX, char cPosY);
	bool			IsValid(Position pos);

	bool			SetMapInfo(Position pos, MapInfo mapInfo);
	bool			SetMapInfo(char cPosX, char cPosY, MapInfo mapInfo);

	MapInfo	GetMapInfo(Position pos, MapInfoType type);
	MapInfo	GetMapInfo(char cPosX, char cPosY, MapInfoType type);

	void			InitMapInfo(MapInfoType type);
	void			DisplayMap(MapInfoType type, char cPosX = ' ', char cPosY = ' ');

private:
	ShipType	m_MapInfo[MAP_SIZE][MAP_SIZE];
	HitResult	m_HitResultMap[MAP_SIZE][MAP_SIZE];
	int				m_ProbabilityMap[MAP_SIZE][MAP_SIZE];
};


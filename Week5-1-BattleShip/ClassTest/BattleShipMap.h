#pragma once
#include "Ship.h"

#define MAP_SIZE	8

class CBattleShipMap
{
public:
	CBattleShipMap(void);
	~CBattleShipMap(void);

	bool		SetMapInfo(Position pos, ShipType shipType);
	bool		SetMapInfo(int nPosX, int nPosY, ShipType shipType);
	ShipType	GetMapInfo(Position pos);
	ShipType	GetMapInfo(int nPosX, int nPosY);
	void		InitMapInfo();
	void		DisplayMap();

protected:
	bool		IsValid(Position pos);

protected:
	ShipType	m_mapInfo[MAP_SIZE][MAP_SIZE];
};


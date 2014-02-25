#pragma once
#include "Ship.h"

#define MAP_SIZE	8
#define MAX_LABEL	8

class CBattleShipMap
{
public:
	CBattleShipMap(void);
	~CBattleShipMap(void);

	bool		SetMapInfo(Position pos, ShipType shipType);
	bool		SetMapInfo(char cPosX, char cPosY, ShipType shipType);
	ShipType	GetMapInfo(Position pos);
	ShipType	GetMapInfo(char cPosX, char cPosY);
	void		InitMapInfo();
	void		DisplayMap();

	void		AddCount(Position pos);
	void		AddCount(char cPosX, char cPosY);
	void		ResetCount();
	int			GetCount(Position pos);
	int			GetCount(char cPosX, char cPosY);
	void		DisplayCount();

	void		SetProbability(Position pos, int turn);

	void		SetProbability(char cPosX, char cPosY, double turn);
	void		SetProbability(char cPosX, char cPosY, int turn);
	int			GetProbability(Position pos);
	int			GetProbability(char cPosX, char cPosY);
	void		InitProbability();
	void		DisplayProbability();

	Position	GetBestProbability();
	int			GetWorstProbabilityValue();

	bool		IsValid(char cPosX, char cPosY);

protected:
	bool		IsValid(Position pos);

protected:
	ShipType	m_MapInfo[MAP_SIZE][MAP_SIZE];
	int			m_CountHistory[MAP_SIZE][MAP_SIZE];
	int			m_Probability[MAP_SIZE][MAP_SIZE];
};


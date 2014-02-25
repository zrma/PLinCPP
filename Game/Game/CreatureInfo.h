#pragma once
#include <string>

#ifndef GAGE_SIZE
#define GAGE_SIZE 5
#endif

enum GAGE
{
	HITPOINT,
	MANAPOINT,
	STAMINAPOINT,
	FURYPOINT,
	BUBBLEPOINT
};

enum CREATURETYPE
{
	PLAYER,
	NPC,
	MOB,
	PET
};

class CCreatureInfo
{
public:
	CCreatureInfo(void);
	~CCreatureInfo(void);

	int				GetGageCurrent(GAGE option) { return m_GageCurrent[option]; }
	int				GetGageMax(GAGE option) { return m_GageMax[option]; }
	CREATURETYPE	GetType() { return m_Type; }

	void			SetGageCurrent(GAGE option, int gageCurrent) { m_GageCurrent[option] = gageCurrent; }
	void			SetGageMax(GAGE option, int gageMax) { m_GageMax[option] = gageMax; }
	void			SetType(CREATURETYPE type) { m_Type = type; }

	std::string		GetName() { return m_Name; }
	void			SetName(std::string name) { m_Name = name; }

private:
	CREATURETYPE	m_Type;
	int				m_GageMax[GAGE_SIZE];
	int				m_GageCurrent[GAGE_SIZE];
	std::string		m_Name;
};


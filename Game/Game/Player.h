#pragma once
#include "creature.h"

class CPlayer :
	public CCreature
{
public:
	CPlayer(void);
	~CPlayer(void);

	void			DisplayStatus();
	void			InitialzeCharacter();
};


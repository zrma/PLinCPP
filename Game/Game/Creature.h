#pragma once
#include "CreatureInfo.h"

class CCreature
{
public:
	CCreature(void);
	virtual ~CCreature(void);

protected:
	CCreatureInfo	m_CreatureInfo;
};


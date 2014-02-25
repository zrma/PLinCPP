#pragma once
#include "character.h"
#include "Minion.h"

class CMob :
	public CCharacter
{
public:
	CMob(void);
	~CMob(void);

	CMinion*	m_pMinion;
	void		Dead();
};


#pragma once
#include "character.h"
class CMob :
	public CCharacter
{
public:
	CMob(void);
	~CMob(void);

	void	Dead();
};


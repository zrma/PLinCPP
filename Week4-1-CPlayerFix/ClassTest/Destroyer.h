#pragma once
#include "ship.h"
class CDestroyer :
	public CShip
{
public:
	CDestroyer(void);
	~CDestroyer(void);

	HitResult	HitCheck(Position hitPos);
};


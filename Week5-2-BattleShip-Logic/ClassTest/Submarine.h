#pragma once
#include "ship.h"
class CSubmarine :
	public CShip
{
public:
	CSubmarine(void);
	~CSubmarine(void);

	HitResult	HitCheck(Position hitPos);
};


#pragma once
#include "ship.h"
class CBattleship :
	public CShip
{
public:
	CBattleship(void);
	~CBattleship(void);

	HitResult	HitCheck(Position hitPos);
};


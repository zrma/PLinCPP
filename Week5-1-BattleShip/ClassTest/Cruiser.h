#pragma once
#include "ship.h"
class CCruiser :
	public CShip
{
public:
	CCruiser(void);
	~CCruiser(void);

	HitResult	HitCheck(Position hitPos);
};


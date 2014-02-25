#include "stdafx.h"
#include "Cruiser.h"


CCruiser::CCruiser(void)
{
	m_Name	= "Cruiser";
	m_HPMAX	= 3;
	m_Type	= CRUISER;
}


CCruiser::~CCruiser(void)
{
}

HitResult CCruiser::HitCheck( Position hitPos )
{
	HitResult result = CShip::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_CRUISER : result;
}

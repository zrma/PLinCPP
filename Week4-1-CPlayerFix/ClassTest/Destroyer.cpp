#include "stdafx.h"
#include "Destroyer.h"


CDestroyer::CDestroyer(void)
{
	m_Name	= "Destroyer";
	m_HPMAX	= 2;
	m_Type	= DESTROYER;
}


CDestroyer::~CDestroyer(void)
{
}

HitResult CDestroyer::HitCheck( Position hitPos )
{
	HitResult result = CShip::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_DESTROYER : result;
}

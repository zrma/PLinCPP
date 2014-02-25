#include "stdafx.h"
#include "Aircraft.h"


CAircraft::CAircraft(void)
{
	m_Name	= "Aircraft";
	m_HPMAX	= 5;
	m_Type		= AIRCRAFT;
}


CAircraft::~CAircraft(void)
{
}

HitResult CAircraft::HitCheck(Position hitPos)
{
	HitResult result = CShip::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_AIRCRAFT : result;
}
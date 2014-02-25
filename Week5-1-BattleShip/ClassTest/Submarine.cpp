#include "stdafx.h"
#include "Submarine.h"


CSubmarine::CSubmarine(void)
{
	m_Name	= "Submarine";
	m_HPMAX	= 1;
	m_Type	= SUBMARINE;
}


CSubmarine::~CSubmarine(void)
{
}

HitResult CSubmarine::HitCheck( Position hitPos )
{
	HitResult result = CShip::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_SUBMARINE : result;
}

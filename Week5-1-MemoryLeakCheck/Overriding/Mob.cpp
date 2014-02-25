#include "stdafx.h"
#include "Mob.h"

CMob::CMob(void)
{
	printf_s("各 积己 \n");
	m_pMinion = new CMinion();
}


CMob::~CMob(void)
{
	delete m_pMinion;
	printf_s("各 昏力 \n");
}

void CMob::Dead()
{
	printf_s("Mob is Dead! \n");
}

#include "stdafx.h"
#include "Mob.h"

CMob::CMob(void)
{
	printf_s("�� ���� \n");
	m_pMinion = new CMinion();
}


CMob::~CMob(void)
{
	delete m_pMinion;
	printf_s("�� ���� \n");
}

void CMob::Dead()
{
	printf_s("Mob is Dead! \n");
}

#include "stdafx.h"
#include "Destroyer.h"


CDestroyer::CDestroyer(void)
{
	printf_s("Create CDestroyer!\n");

	m_Name	= "Destroyer";
	m_HPMAX	= 2;
	m_Type	= DESTROYER;
}


CDestroyer::~CDestroyer(void)
{
	printf_s("Destroy CDestroyer!\n");
}

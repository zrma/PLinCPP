#include "stdafx.h"
#include "Cruiser.h"


CCruiser::CCruiser(void)
{
	printf_s("Create CCruiser!\n");

	m_Name	= "Cruiser";
	m_HPMAX	= 3;
	m_Type	= CRUISER;
}


CCruiser::~CCruiser(void)
{
	printf_s("Destroy CCruiser!\n");
}

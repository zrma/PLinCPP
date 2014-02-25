#include "stdafx.h"
#include "Aircraft.h"


CAircraft::CAircraft(void)
{
	printf_s("Create CAircraft!\n");
	
	m_Name	= "Aircraft";
	m_HPMAX	= 5;
	m_Type	= AIRCRAFT;
}


CAircraft::~CAircraft(void)
{
	printf_s("Destroy CAircraft!\n");
}

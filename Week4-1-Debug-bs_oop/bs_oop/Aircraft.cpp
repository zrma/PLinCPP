#include "stdafx.h"
#include "Aircraft.h"


CAircraft::CAircraft(void)
{
	//printf_s("Create Aircraft\n");

	m_HP = 5;
	m_Type = AIRCRAFT;
	m_Name  = "Aircraft";
}


CAircraft::~CAircraft(void)
{
	//printf_s("Destroy Aircraft\n");
}

#include "stdafx.h"
#include "Submarine.h"


CSubmarine::CSubmarine(void)
{
	printf_s("Create CSubMarine!\n");
	
	m_Name	= "Submarine";
	m_HPMAX	= 1;
	m_Type	= SUBMARINE;
}


CSubmarine::~CSubmarine(void)
{
	printf_s("Destroy CSubMarine!\n");
}

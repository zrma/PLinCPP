#include "stdafx.h"
#include "WellRandom.h"
#include <stdlib.h>
#include <time.h>

CWellRandom* CWellRandom::m_pInstance = NULL;

CWellRandom::CWellRandom(void)
{
	m_WellIndex = 0;

	srand((unsigned long)time(NULL));

	for(int i = 0; i < 16; ++i)
	{
		m_WellState[i] = rand();
	}
}

CWellRandom::~CWellRandom(void)
{

}

unsigned long CWellRandom::WELLRNG512(void)
{
	unsigned long a, b, c, d;

	a = m_WellState[m_WellIndex];
	c = m_WellState[(m_WellIndex + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = m_WellState[(m_WellIndex + 9) & 15];
	c ^= (c >> 11);
	a = m_WellState[m_WellIndex] = b ^ c;
	d = a ^ ((a << 5) & 0xDA442D20UL);
	m_WellIndex = (m_WellIndex + 15) & 15;
	a = m_WellState[m_WellIndex];
	m_WellState[m_WellIndex] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

	return m_WellState[m_WellIndex];
}

unsigned long CWellRandom::WellRand(int r)
{
	return WELLRNG512() % r;
};

// »çÀÌ °ª ·£´ý
unsigned long CWellRandom::WellRandom(int nMin, int nMax)
{
	return (nMin + WellRand(nMax - nMin + 1));
}

CWellRandom* CWellRandom::GetInstance()
{
	if(m_pInstance)
		return m_pInstance;
	else
	{
		m_pInstance = new CWellRandom();
		return m_pInstance;
	}
}

void CWellRandom::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}
#pragma once

class CWellRandom
{
private:
	CWellRandom(void);
public:
	~CWellRandom(void);

public:
	unsigned long WELLRNG512(void);
	unsigned long WellRand(int r);
	unsigned long WellRandom(int nMin, int nMax);

public:
	static CWellRandom*	GetInstance();
	static void					ReleaseInstance();

private:
	static CWellRandom*	m_pInstance;

private:
	unsigned long m_WellState[16];
	unsigned long m_WellIndex;
};

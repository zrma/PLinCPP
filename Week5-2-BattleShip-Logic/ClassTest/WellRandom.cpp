#include "stdafx.h"
#include "WellRandom.h"
#include <stdlib.h>
#include <time.h>

static unsigned long wellState[16];
static unsigned long wellIndex = 0;

void InitWELLRNG(void)
{
	srand((unsigned long)time(NULL));
	for(int i = 0; i < 16; ++i)
	{
		wellState[i] = rand();
	}
}

unsigned long WELLRNG512(void)
{
	unsigned long a, b, c, d;

	a = wellState[wellIndex];
	c = wellState[(wellIndex+13)&15];
	b = a^c^(a<<16)^(c<<15);
	c = wellState[(wellIndex+9)&15];
	c ^= (c>>11);
	a = wellState[wellIndex] = b^c;
	d = a^((a<<5)&0xDA442D20UL);
	wellIndex = (wellIndex + 15)&15;
	a = wellState[wellIndex];
	wellState[wellIndex] = a^b^d^(a<<2)^(b<<18)^(c<<28);

	return wellState[wellIndex];
}

unsigned long WellRand(int r)
{
	return WELLRNG512() % r;
};

// »çÀÌ °ª ·£´ý
unsigned long WellRandom(int nMin, int nMax)
{
	return (nMin + WellRand(nMax - nMin + 1));
}

#pragma once
#include <windows.h>

enum SoundSet
{
	A,
	B,
	C,
	D
};

class CSoundUI
{
public:
	CSoundUI(void);
	~CSoundUI(void);

public:
	void		Sound(SoundSet soundType) { Beep(((int)(soundType) + 4) * 100, 1000); }

};


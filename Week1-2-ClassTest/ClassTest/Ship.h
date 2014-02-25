#pragma once
class cShip
{
public:
	cShip(void);
	~cShip(void);

	int hp_current;
	int type_code;

	int hitCheck();
};


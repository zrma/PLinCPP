#pragma once
class cMap
{
public:
	cMap(void);
	~cMap(void);

	int row_size;
	int col_size;
	int* map_data;

	int initMap();
	int inputMapData();
	int printMap();
};


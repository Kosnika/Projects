#pragma once
#include "Win10.h"
// Map
// // Coord 0 -> x, y int (size_t)
// Player   ->  Cooord 


struct Coord
{
	int x;
	int y;
};


struct Player
{
	Coord position;
	size_t currentNumberOfKeys;
};



struct Map
{
	std::string* map;
	size_t h;
	size_t w;
	Player player;
	size_t maxNumberOfKeys;

	void DrawMap()
	{
		SetPos(0, 0);
		for (int i = 0; i < h; i++)
		{
			std::cout << map[i] << std::endl;
		}
	}
};

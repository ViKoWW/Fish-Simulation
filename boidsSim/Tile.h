#pragma once
#ifndef TILE_H
#define TILE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class Tile
{
public:
	

	Tile(int pixelPosX,
		int pixelPosY,
		int tileNumX,
		int tileNumY
		);
	~Tile();
};

#endif

#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "FastNoiseLite.h"
#include "Tile.h"


//sets up the screen width and the column and rows and their sizes
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
const int res = 10;


class Terrain : public sf::Drawable , public sf::Transformable 
{
private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &myTexture;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(myVertices, states);
	}

	//the vector which shall hold the noise values for the cave terrain 

	
	sf::VertexArray myVertices;
	sf::Texture myTexture;
	int getState(int a, int b, int c, int d);
	
	void generateNoise();

public:

	Terrain();
	~Terrain();

	int cols;
	int rows;

	std::vector<std::vector<Tile>> tileVec;
	std::vector<std::vector<float>> field;
	std::vector<std::vector<sf::CircleShape>> circleField;

	void generateTerrain();
	void drawTerrain();


};


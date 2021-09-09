#pragma once
#ifndef FISH_H
#define FISH_H

#define PI 3.14159265

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include<math.h>
#include <random>
//#include "School.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Fish : public sf::Drawable, public sf::Transformable
{

private: 
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &myFishTexture;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(myFishVertices, states);
	}

	//the vector which shall hold the noise values for the cave terrain 


	sf::VertexArray myFishVertices;
	sf::Texture myFishTexture;

	int fishW = 10;
	int fishH = 15;
	float randomfloat(int range);
	
	sf::Color color;
	sf::Vector2f pos;
	sf::Vector2f velocityVec;
	/*
	sf::Vector2f coherence(int fishNum, int schoolSize);
	
	sf::Vector2f spacing(int fishNum, int schoolSize);
	sf::Vector2f matchVel(int fishNum, int schoolSize);

	int visual_range = 240;
	int neigborhoodRange = 200;
	float fov = 90;
	*/
public:

	bool generateFish();
	void updateFish(Fish* fish);
	void rotateFish(Fish* fish, double ang);
	sf::Sprite sprite;
	sf::VertexArray myFish;
	Fish();
	Fish(sf::Vector2f startingPos, sf::Color color);
	~Fish();
	
	float getRandom(float num1, float num2);



};

#endif
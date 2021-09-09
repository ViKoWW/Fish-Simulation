#pragma once

#ifndef SCHOOL_H
#define SCHOOL_H

#include "Fish.h"
#include <random>
#include <iostream>

const int  schoolSize = 100;

class School
{
	
private:
	float spawnSize = 100;
	float xpos, ypos;
	float getRandom(float num1, float num2);
	sf::Color color;
public:
	bool spawnSchool();
	Fish schoolArr[schoolSize];
	School(float xpos, float ypos, sf::Color color);
	~School();
};

#endif
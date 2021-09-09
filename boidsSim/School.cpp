#include "School.h"





School::School(float xpos, float ypos, sf::Color color)
{
	this->xpos = xpos;
	this->ypos = ypos;
	this->color = color;

}
School::~School()
{
}

bool School::spawnSchool()
{
	for (int i = 0; i < schoolSize; i++) {
		//creates the array of Fish objects
		schoolArr[i] = Fish(sf::Vector2f(getRandom(xpos, xpos + spawnSize), getRandom(ypos, ypos + spawnSize)), color);
		schoolArr[i].generateFish();
		schoolArr[i].rotateFish(&schoolArr[i], 10.f);
		schoolArr[i].updateFish(&schoolArr[i]);
		//std::cout << "working";
		//}

		
	}
	return true;
}

float School::getRandom(float num1, float num2)
{

	std::random_device rd; //obtains random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(num1, num2); //defines the range

	return distr(gen);

}


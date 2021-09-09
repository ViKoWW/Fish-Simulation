#include "Fish.h"

Fish::Fish() {
	pos = sf::Vector2f(100.f,100.f);
}

Fish::Fish(sf::Vector2f startingPos, sf::Color color)
{
	//loads the texture goldfish.png 
	sf::Texture texture;
	if (!texture.loadFromFile("images/goldfish.png"))
	{
		std::cout << "ERROR, COULD NOT FIND FILE 'image.png'";
	}
	texture.setSmooth(true);

	//binds the texture to the sprite created with the object
	sprite.setTexture(texture);
	//generates a 2d vector with random values between 1 and the screen width/height
	pos = startingPos;
	this->color = color;
	///sets the position to the vector startingpos, here is the position in which the fish spawns
	sprite.setPosition(startingPos);
	
}


//function for creating a random float number in specified range
float Fish::randomfloat(int range)
{																																				
	int num = rand() % range + 1;
	float fnum = static_cast<float>(num);
	return fnum;

}


Fish::~Fish()
{
}

bool Fish::generateFish() {

	myFishVertices.setPrimitiveType(sf::Triangles);
	myFishVertices.resize(3);
	
	velocityVec = sf::Vector2f(getRandom(0, 1.f), getRandom(0, 1.f));

	myFishVertices[0] = pos;
	myFishVertices[1] = sf::Vector2f(pos.x + fishW, pos.y);
	myFishVertices[2] = sf::Vector2f(pos.x + fishW/2, pos.y-fishH);

	myFishVertices[0].color = color;
	myFishVertices[1].color = color;
	myFishVertices[2].color = color;

	return true;
}

void Fish::updateFish(Fish* fish)
{

	fish->pos += velocityVec;

	myFishVertices[0] = pos;
	myFishVertices[1] = sf::Vector2f(pos.x + fishW, pos.y);
	myFishVertices[2] = sf::Vector2f(pos.x + fishW / 2, pos.y - fishH);
	double x, y, result;
	result = atan2(velocityVec.y, velocityVec.x) * 180 / PI;
	fish->setRotation(result);
}

void Fish::rotateFish(Fish* fish, double ang)
{
	double x, y, result;
	result = atan2(velocityVec.y, velocityVec.x);
	fish->setRotation(getRandom(-ang, ang));

}

float Fish::getRandom(float num1, float num2)
{

	std::random_device rd; //obtains random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(num1, num2); //defines the range

	return distr(gen);

}
//checks for coherence, that is trying to get the fishes to move to the center mass of the school

/*
sf::Vector2f Fish::coherence(int fishNum, int schoolSize, School* school)
{
	sf::Vector2f centerMass;
	int neighborNum;
	float massHolder;
	//loops through all fishes to calculate the center mass which an individual fishNum would encounter
	for (int i = 0; i < schoolSize; i++) 
	{

		if (i != fishNum )
		{
			//adds the position vector of object i to the centerMass vector
			centerMass += school->schoolArr[i].pos;
			//adds the amount of neighbors counted to be used for the division later
			neighborNum++;

		}
		

	}
	
	centerMass = centerMass / static_cast<float>(neighborNum); //divides the mass by the numbers of neighbors
	centerMass -= school->schoolArr[fishNum].pos; //subtracts the position of the fish passed into the function
	centerMass = centerMass / 100.f; //divides by 100 to get a more graduall movement correction
	return centerMass;
}



sf::Vector2f Fish::spacing(int fishNum, int schoolSize)
{
	return sf::Vector2f(2.f, 2.f);
}


sf::Vector2f Fish::matchVel(int fishNum, int schoolSize)
{
	return sf::Vector2f(2.f, 2.f);

}

*/
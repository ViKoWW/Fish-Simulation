#include "Terrain.h"



Terrain::Terrain()
{
	 cols = SCREEN_WIDTH*2 / res;
	 rows = SCREEN_HEIGHT / res;
}


Terrain::~Terrain()
{
}

void Terrain::generateTerrain() 
{

	for (int i = 0; i < cols+1; i++) {
		circleField.push_back(std::vector<sf::CircleShape>());
		field.push_back(std::vector<float>());
		for (int j = 0; j < rows+1; j++) {
			//generates a random number between 0 and 1 and feeds it into the matrix. 
		//	field[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			circleField[i].push_back(sf::CircleShape(2.f));
			
			field[i].push_back(1.f);
		}
	}


	// Create and configure FastNoise object
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetFrequency(0.03);
	// Gather noise data
	auto noiseData = new float[54][36];
	
	int index = 0;

	for (int y = 0; y < cols; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			//generetas the noise to the field matrix
			field[y][x] = (noise.GetNoise((float)y, (float)x));
			
			//std::cout << field[y][x] << " ";
		}
	}


	for (int a = 0; a < cols; a++)
	{
		for (int b = 0; b < rows; b++)
		{
			//sets the field array equal to the noise values ceiled to either 0 or 1. 
			field[a][b] = ceil(field[a][b]);
			//if (field[a][b] == -1 || field[a][b] == -0)
			//	field[a][b] == 0;
			//std::cout << field[y][x] << " ";
		}
	}
	
	for (int n = 0; n < cols * 2; n++) 
	{
		tileVec.push_back(std::vector<Tile>());
		for (int o = 0; o < rows * 2; o++)
		{

			tileVec[n].push_back(Tile(n * (res / 2), o * (res / 2), n, o));

		}
	}
	// Do something with this data...

	// Free data later


}

void Terrain::drawTerrain()
{

	myVertices.setPrimitiveType(sf::Triangles);
	myVertices.resize(cols * rows * 9 );

	if (!myTexture.loadFromFile("images/testterrain.jpg"))
		std::cout << "COULD NOT LOAD TEXTURE";
	
	//loops through the field of cols and rows
	for (unsigned int i = 0; i < cols-1; i++) {
		for (unsigned int j = 0; j < rows-1; j++) {
			
			//pointer to the current line
			//the number refers to the max amount of vertex points per iteration, in this case it is 9 
			sf::Vertex* line = &myVertices[(i + j * cols) * 9 ];

			//sets the vertex points of the abcd parts of the squares, this will be used for drawing the lines of the algorithm

			sf::Vector2f a = sf::Vector2f(i * res + (res*0.5), j * res);
			sf::Vector2f b = sf::Vector2f((i+1) * res, (j+1) * res - (res*0.5));
			sf::Vector2f c = sf::Vector2f(i * res + (res*0.5), (j+1) * res);
			sf::Vector2f d = sf::Vector2f(i * res , (j+1) * res - (res*0.5));

			//the vertex points of the corners of the squares

			sf::Vector2f x = sf::Vector2f(i * res  , j * res);
			sf::Vector2f y = sf::Vector2f((i+1) * res  , j * res);
			sf::Vector2f z = sf::Vector2f((i + 1) * res  , (j+1)* res);
			sf::Vector2f w = sf::Vector2f(i * res  , (j + 1) * res);

		//colors the dots black and white
			int colVal = field[i][j];
			if (colVal == 1)
				colVal = 255;
			//positions the dots correctly
			circleField[i][j].setPosition(i * res, j * res);
			circleField[i][j].setFillColor(sf::Color(colVal, colVal, colVal));

			//gets the state of the quadrant
			int state = getState(field[i][j], field[i+1][j], field[i+1][j+1], field[i][j+1]);
			
			//matches the state of the noise quadrant with the correct marching cube case, there are 16 different cases all corresponding to a unique geometry.
			switch (state)
			{
			case 0:
				
				break;
			case 1:
				line[0].position = w;
		    	line[1].position = c;
				line[2].position = d;
			//	std::cout << w.x << " " << w.y << " ";
				break;
			case 2:
				line[0].position = b;
				line[1].position = c;
				line[2].position = z;
				break;
			case 3:
				line[0].position = b;
				line[1].position = d;
				line[2].position = z;

				line[3].position = d;
				line[4].position = w;
				line[5].position = z;
				break;
			case 4:
				line[0].position = a;
				line[1].position = b;
				line[2].position = y;
				break;
			case 5:
				line[0].position = a;
				line[1].position = d;
				line[2].position = x;

				line[3].position = b;
				line[4].position = c;
				line[5].position = z;
				break;
			case 6:
				line[0].position = a;
				line[1].position = c;
				line[2].position = z;

				line[3].position = z;
				line[4].position = a;
				line[5].position = y;
				break;
			case 7:
				line[0].position = a;
				line[1].position = d;
				line[2].position = w;

				line[3].position = w;
				line[4].position = a;
				line[5].position = y;

				line[6].position = w;
				line[7].position = y;
				line[8].position = z;
				break;
			case 8:
				line[0].position = a;
				line[1].position = d;
				line[2].position = x;
				break;
			case 9:
				line[0].position = a;
				line[1].position = c;
				line[2].position = w;

				line[3].position = w;
				line[4].position = x;
				line[5].position = a;
				break;
			case 10:
				line[0].position = a;
				line[1].position = b;
				line[2].position = y;

				line[3].position = c;
				line[4].position = d;
				line[5].position = w;
				break;
			case 11:
				line[0].position = a;
				line[1].position = b;
				line[2].position = z;

				line[3].position = z;
				line[4].position = a;
				line[5].position = x;

				line[6].position = x;
				line[7].position = w;
				line[8].position = z;
				break;
			case 12:
				line[0].position = b;
				line[1].position = d;
				line[2].position = x;

				line[3].position = x;
				line[4].position = y;
				line[5].position = b;
				break;
			case 13:
				line[0].position = b;
				line[1].position = c;
				line[2].position = y;

				line[3].position = c;
				line[4].position = y;
				line[5].position = x;

				line[6].position = x;
				line[7].position = w;
				line[8].position = c;
				break;
			case 14:
				line[0].position = c;
				line[1].position = d;
				line[2].position = x;

				line[3].position = x;
				line[4].position = c;
				line[5].position = y;

				line[6].position = y;
				line[7].position = c;
				line[8].position = z;
				break;
			case 15:
				line[0].position = x;
				line[1].position = y;
				line[2].position = z;

				line[3].position = z;
				line[4].position = w;
				line[5].position = x;
				break;








			}


			
		}
	}
}
//converts 4 bit number to base 10
int Terrain::getState(int a, int b, int c, int d) {

	return a * 8 + b * 4 + c * 2 + d * 1;

}

void Terrain::generateNoise() {


}
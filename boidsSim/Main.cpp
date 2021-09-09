#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Terrain.h"
#include "Fish.h"
#include "School.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
int main()
{



	float dt = 0.f;
	sf::Clock dtClock;
	float elapsed;

	sf::Clock elapsedClock;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "MARCHING CUBES");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Terrain terrain;
	
	Fish fish;
	fish.generateFish();
	terrain.generateTerrain();
	terrain.drawTerrain();

	School school1(100.f, 100.f, sf::Color::Red);
	school1.spawnSchool();
	School school2(500.f, 250.f, sf::Color::Green);
	school2.spawnSchool();
	sf::View mapView;
	mapView.setSize(1024.f, 512.f);
	mapView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
	float viewSpeed = 200.f;


	while (window.isOpen())
	{




		//update dt
		elapsed = elapsedClock.getElapsedTime().asSeconds();

		if (elapsed > 0.1f)
			elapsedClock.restart();

		dt = dtClock.restart().asSeconds();

		//events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			//mouse scroll zoom
			else if (event.type == sf::Event::MouseWheelScrolled)
			{

				if (event.mouseWheelScroll.delta < 0)
					mapView.zoom(1.1f);

				else {
					mapView.zoom(0.9f);
				}

			}

		}



		//Update
		//Update view 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left
		{
			mapView.move(-viewSpeed * dt, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right
		{
			mapView.move(+viewSpeed * dt, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
		{
			mapView.move(0.f, -viewSpeed * dt);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //down
		{
			mapView.move(0.f, +viewSpeed * dt);
		}

		window.clear(sf::Color(200, 200, 200));
		window.setView(mapView);

		//draws the dots
		/*for (int i = 0; i < terrain.cols; i++) {
			for (int j = 0; j < terrain.rows; j++) {
				window.draw(terrain.circleField[i][j]);
			}
		}*/
		//draws the main cave terrain
	

		window.draw(terrain);
	//	window.draw();
		for (int i = 0; i < 100; i++)
		{
			school1.schoolArr[i].updateFish(&school1.schoolArr[i]);
			school1.schoolArr[i].updateFish(&school2.schoolArr[i]);
			window.draw(school1.schoolArr[i]);
			window.draw(school2.schoolArr[i]);
		}

		window.draw(fish);

		window.setView(window.getDefaultView());

		window.display();
	}

	return 0;
}
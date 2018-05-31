#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "vehicle.h"
#include "vehicleSystem.h"

using namespace std;
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	Clock clock;
	/*
	//for testing purposes
	float testForce = 10;
	float posX = 100;
	float posY = 100;
	float velX = 4;
	float velY = 4;
	float accelX = 5;
	float accelY = 5;
	

	CircleShape shape(10, 3);
	shape.setFillColor(sf::Color::White);
	

	vehicle testVehicle(shape, posX, posY, velX, velY, &window);
	//end of testing stuff
	*/

	//test two
	vehicleSystem testSys(&window);

	while (window.isOpen())
	{
		sf::Event event;

		float dt = clock.restart().asSeconds();


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//test update
		//window.draw(*testVehicle.updateVehicle(dt));

		//doesn't wor here
		//window.draw(testSys.updateVehicleSystem(dt));

		//Debug Center
		//sf::CircleShape centerCircle(5, 50);
		//centerCircle.setPosition(testVehicle.pos);
		//centerCircle.setOrigin(centerCircle.getLocalBounds().width / 2, centerCircle.getLocalBounds().height / 2);
		//window.draw(centerCircle);

		window.display();
		window.clear();
	}

	return 0;
}

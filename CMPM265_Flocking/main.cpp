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

	//Make a vehicle system for the simulation
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


		//Make the vehicle system update
		testSys.updateVehicleSystem(dt);
		
		//draw each vehicle in the vehicle system
		for (int i = 0; i < testSys.vSystem.size(); i++) {
			//turns on seperation
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				testSys.vSystem[i].sepOn = true;
			}
			//turns off seperation
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				testSys.vSystem[i].sepOn = false;
			}
			//turns on alignment
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				testSys.vSystem[i].alignOn = true;
			}
			//turns off alignment
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				testSys.vSystem[i].alignOn = false;
			}
			//turns on cohesion
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				testSys.vSystem[i].cohOn = true;
			}
			//turns off alignment
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
				testSys.vSystem[i].cohOn = false;
			}

			//Draw the vehicles 
			window.draw(testSys.vSystem[i].vehicleShape);
		}

		window.display();
		window.clear();
	}

	return 0;
}

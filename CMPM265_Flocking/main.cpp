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

	//Make a vehicle system
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

			window.draw(testSys.vSystem[i].vehicleShape);
		}

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

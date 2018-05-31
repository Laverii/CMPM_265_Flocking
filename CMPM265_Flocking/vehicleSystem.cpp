#include "vehicleSystem.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "vehicle.h"

vehicleSystem::vehicleSystem(RenderWindow *window)
{
	//set the velocity values
	velocityX = 4;
	velocityY = 4;

	//Set the shape of the vehicles
	//*vehicleShape(10, 3);

	//set the window
	theWindow = window;
}

//updates the vehicle system
void vehicleSystem::updateVehicleSystem(float dt) {

	//get the mouse position
	Vector2f targetPos = Vector2f(Mouse::getPosition(*theWindow));

	//draw the vehicles
	for(int i = 0; i < vSystem.size(); i++) {

		//if the button has been pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//create a new vehicle
			vehicle newVehicle(targetPos.x, targetPos.y, velocityX, velocityY);
			//push it bac into the vector
			vSystem.push_back(newVehicle);
		}

		//removes the vehicle
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			//erase the vehicle
			vSystem.erase(vSystem.begin() + 1);
		}

		vSystem[i].updateVehicle(dt, targetPos);
	}


}

vehicleSystem::~vehicleSystem()
{
}

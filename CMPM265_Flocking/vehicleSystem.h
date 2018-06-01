#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector> 
#include <cmath>
#include "vehicle.h"

using namespace std;
using namespace sf;

class vehicleSystem
{
public:

	//create a system of vehicles
	vector<vehicle> vSystem;
	//Window of the SFML
	RenderWindow *theWindow;
	//Set the velocities
	float velocityX;
	float velocityY;

	//Constructs the vehicleSystem class
	vehicleSystem(RenderWindow*);
	//updates the vehicle system
	void vehicleSystem::updateVehicleSystem(float);
	//Sperates the vehicles form each other.
	void seperation(vector<vehicle>);
	~vehicleSystem();
};


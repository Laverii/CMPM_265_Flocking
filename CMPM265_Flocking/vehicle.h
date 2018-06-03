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

using namespace std;
using namespace sf;


class vehicle
{
public:

	sf::ConvexShape vehicleShape;
	sf::Vector2f vel;
	sf::Vector2f pos; 
	sf::Vector2f accel;
	//RenderWindow *theWindow;
	float maxForce;
	float maxSpeed;
	float radius;
	bool sepOn;
	bool cohOn;
	bool alignOn;

	vehicle();
	//vehicle(CircleShape, float, float, float, float, RenderWindow*);
	//constructor of vehicle
	vehicle(float, float, float, float);
	//Update vehicle's position
	sf::ConvexShape*vehicle::updateVehicle(float, Vector2f);
	//Searches for target
	void vehicle::search(Vector2f);
	//Applies acceleration
	void vehicle::acceleration(Vector2f);
	//Applies seperation behavior
	Vector2f vehicle::seperation(vector<vehicle>);
	//Applies the alignment behavior
	Vector2f vehicle::alignment(vector<vehicle>);
	//Applies the cohesion behavior
	Vector2f vehicle::cohesion(vector<vehicle>);
	//aplies the behaviors to the system
	void vehicle::applyBehaviors(vector<vehicle>);
	~vehicle();
};


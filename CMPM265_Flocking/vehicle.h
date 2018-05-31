#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

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

	vehicle();
	//vehicle(CircleShape, float, float, float, float, RenderWindow*);
	vehicle(float, float, float, float);
	sf::ConvexShape*vehicle::updateVehicle(float, Vector2f);
	void vehicle::search(Vector2f);
	void vehicle::acceleration(Vector2f);
	~vehicle();
};


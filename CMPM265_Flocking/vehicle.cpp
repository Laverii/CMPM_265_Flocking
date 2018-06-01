#include "vehicle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "vectorMath.h"

using namespace std;
using namespace sf;

//sets up the parameter for the vehicle class
vehicle::vehicle(float posX, float posY, float velX, float velY)
{
	//sets up the shape of vehicle
	vehicleShape.setPointCount(3);
	vehicleShape.setPoint(0, sf::Vector2f(pos.x,pos.y));
	vehicleShape.setPoint(1, sf::Vector2f(pos.x - 5, pos.y + 10));
	vehicleShape.setPoint(2, sf::Vector2f(pos.x - 5, pos.y - 10));
	vehicleShape.setFillColor(sf::Color::White);
	//Set the x position
	pos.x = posX;
	//Set the y position
	pos.y = posY;
	//set the x velocity
	vel.x = velX;
	//Set the y velocity
	vel.y = velY;
	//Set the maximum force
	maxForce = 200;
	//Set the max speed
	maxSpeed = 200;
	//Set the center
	vehicleShape.setOrigin(vehicleShape.getLocalBounds().width / 2, vehicleShape.getLocalBounds().height / 2);
	//theWindow = window;
	//set the initial acceleration
	accel.x = 100;
	accel.y = 100;
}

//Add acceleration
void vehicle::acceleration(Vector2f force) {
	//adds the force to the acceleration
	accel = accel + force;
}

//searches for the target
void vehicle::search(Vector2f target) {
	//where you want to go
	Vector2f desired;
	desired = target - pos;

	//Normalize the vector
	desired = vectorMath::normalize(desired);

	//multiply by max force
	desired = desired * maxForce;

	//Steer the vehicle
	Vector2f steer;
	steer = desired - vel;

	//limit steer by the maximum force
	Vector2f limitVector = vectorMath::limit(steer, maxForce);

	//then apply the force with the acceleration
	acceleration(limitVector);

	//get the rotation and change it
	float radians = atan2(steer.y, steer.x);
	vehicleShape.setRotation(radians* 52.2958f);

}

//Updates the position of the vehicle
ConvexShape *vehicle::updateVehicle(float dt, Vector2f targetPos) {

	//Set the mouse
	//Vector2f targetPos = Vector2f(Mouse::getPosition(*theWindow));

	//call search
	search(targetPos);

	//Adds acceleration to velocity to help the vehicle move. 
	vel += accel * dt;

	//resets the acceleration for next frame (update root)
	accel = accel * 0.0f;

	//updates the position
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;


	//if it is outside the window (x direction)
	if (pos.x > 800 || pos.x < 0) {
		vel.x = -vel.x;
	}

	//if it is outside the window (y direction)
	if (pos.y > 600 || pos.y < 0) {
		vel.y = -vel.y;
	}

	//set the position
	vehicleShape.setPosition(pos.x, pos.y);

	//return the vehicle shape
	return &vehicleShape;
}


vehicle::~vehicle()
{
}

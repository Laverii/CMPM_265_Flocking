#include "vehicle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "vectorMath.h"
#include <vector> 
#include <cmath>

using namespace std;
using namespace sf;

//sets up the parameter for the vehicle class
vehicle::vehicle(float posX, float posY, float velX, float velY)
{
	//radius
	radius = 5;
	//sets up the shape of vehicle
	vehicleShape.setPointCount(3);
	vehicleShape.setPoint(0, sf::Vector2f(pos.x,pos.y));
	vehicleShape.setPoint(1, sf::Vector2f(pos.x - radius, pos.y + radius*2));
	vehicleShape.setPoint(2, sf::Vector2f(pos.x - radius, pos.y - radius*2));
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
	//set the initial acceleration
	accel.x = 100;
	accel.y = 100;
	//booleans for applying forces
	sepOn = false;
	alignOn = false;
	cohOn = false;
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

//Seperation behavior between the vehicles
Vector2f vehicle::seperation(vector<vehicle> vehicleVector) {
	
	//Find how far I want each vehicle to be
	float desiredSep = radius * 2;
	//Get the sum
	Vector2f sum;
	//count the amnt of cars within the vicnity
	float cnt = 0.0f;

		//loop through all the vehicles in the vector
		for (int i = 0; i < vehicleVector.size(); i++) {
			//find the distance between sqrt((x2 - x1) - (y2- y1))
			float distance = sqrt((pos.x - vehicleVector[i].pos.x) + (pos.y - vehicleVector[i].pos.y));

			//if the distance is more than 0 but less than the desired seperation (nearby the cars)
			if ((distance > 0) && (distance < desiredSep)) {

				//FInd the difference between the two positions
				Vector2f difference = pos - vehicleVector[i].pos;
				//Normalize the vector
				difference = vectorMath::normalize(difference);
				//divide the difference by the distance
				difference = difference / distance;
				//add the difference to the sum
				sum = sum + difference;
				//increase the count
				cnt++;
			}
		}//end for loop

		//if there are several cars within the vincity
	if (cnt > 0) {
		//divide the sum by the count
		sum = sum / cnt;
		//normalize the sum
		sum = vectorMath::normalize(sum);
		//Multiply the sum by the maxspeed
		sum = sum * maxSpeed;
		//get the steer
		Vector2f steer = sum - vel;
		//limit the steering
		steer = vectorMath::limit(steer, maxForce);
		//add the acceleration in
		//acceleration(steer);
		return steer;
	}
	else {
		return Vector2f(0.0f, 0.0f);
	}
}

//Provides alignment behavior to the vehicles
Vector2f vehicle::alignment(vector<vehicle> vehicleVector) {
	//neighbor float
	float neighbors = 40.0f;
	//make a sum vector
	Vector2f sum;
	//create a count
	float cnt = 0.0f;

	//loop through the vehicle vector
	for (int i = 0; i < vehicleVector.size(); i++) {
		//find the distance between sqrt((x2 - x1) - (y2- y1))
		float distance = sqrt((pos.x - vehicleVector[i].pos.x) - (pos.y - vehicleVector[i].pos.y));

		//if the distance is greater than 0 and the distance is less than the neighbor
		if ((distance > 0) && (distance < neighbors)){
			//add the velocity
			sum = sum + vehicleVector[i].vel;
			//Increase the count
			cnt++;
		}
	}//end for loop

	//if there is more than one vehicle nearby
	if (cnt > 0) {
		//divide the sum by the count
		sum = sum / cnt;
		//normalize the sum
		sum = vectorMath::normalize(sum);
		//Multiply the sum by the maxspeed
		sum = sum * maxSpeed;
		//get the steer
		Vector2f steer = sum - vel;
		//add the acceleration in
		//acceleration(steer);
		//return the steer
		return steer;
	}
	else {
		//returns an empty vector 2f
		return Vector2f(0, 0);
	}
}

Vector2f vehicle::cohesion(vector<vehicle> vehicleVector) {
	//neighbor float
	float neighbors = 40.0f;
	//make a sum vector
	Vector2f sum;
	//create a count
	float cnt = 0.0f;

	//loop through the vehicle vector
	for (int i = 0; i < vehicleVector.size(); i++) {
		//find the distance between sqrt((x2 - x1) - (y2- y1))
		float distance = sqrt((pos.x - vehicleVector[i].pos.x) - (pos.y - vehicleVector[i].pos.y));

		//if the distance is greater than 0 and the distance is less than the neighbor
		if ((distance > 0) && (distance < neighbors)) {
			//add the velocity
			sum = sum + vehicleVector[i].vel;
			//Increase the count
			cnt++;
		}
	}//end for loop

	 //if there is more than one vehicle nearby
	if (cnt > 0) {
		//divide the sum by the count
		sum = sum / cnt;
		//search for the sum
		search(sum);
		//and return it
		return sum;
	}
	else {
		//returns an empty vector 2f
		return Vector2f(0, 0);
	}
}

//Applies the behaviors to the vehicles
void vehicle::applyBehaviors(vector<vehicle>vehicleVector) {
	
	//apply seperation	
	Vector2f seperate;
	if (sepOn == true) {
		//applies sepertion
		seperate = seperation(vehicleVector);
	}
	else {
		//set it to normal
		seperate = Vector2f(0.0f, 0.0f);
	}

	//apply alignment
	Vector2f align;

	if (alignOn == true) {
		//applies alignment
		align = alignment(vehicleVector);
	}
	else {
		//set it bac to normal
		align = Vector2f(0.0f, 0.0f);
	}

	//apply cohesion
	Vector2f cohe;

	if (cohOn == true) {
		//applies cohesion
		cohe = cohesion(vehicleVector);
	}
	else {
		//set it bac to normal
		cohe = Vector2f(0.0f, 0.0f);
	}

	//apply the foces
	acceleration(seperate);
	acceleration(align);
	acceleration(cohe);
}


vehicle::~vehicle()
{
}

#include "vectorMath.h"



vectorMath::vectorMath()
{
}

//FInds the magnitude of the vector
float vectorMath::magnitude(Vector2f vector) {
	
	//get magnitude
	float magni = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

	//help prevent divide by 0 
	if (magni == 0) {
		magni = 0.000000000001;
	}

	//return the value
	return magni;
}

//Normalizes the vector
Vector2f vectorMath::normalize(Vector2f vector) {

	//finds the magnitude of the vector
	float magni = magnitude(vector);
	//normalizes the vector by its magnitude
	Vector2f normalizedVector = vector / magni;

	return normalizedVector;

}

Vector2f vectorMath::limit(Vector2f vector, float length) {
	//get magnitude
	float magni = magnitude(vector);

	//if magnitude is greater than the length
	if (magni > length) {
		magni = length;
	}

	//normalized the vector
	Vector2f normalizedVector = normalize(vector);
	
	return normalizedVector * magni;

}

vectorMath::~vectorMath()
{
}

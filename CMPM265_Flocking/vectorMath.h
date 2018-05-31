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

class vectorMath
{
public:

	vectorMath();
	static float vectorMath::magnitude(Vector2f);
	static Vector2f vectorMath::normalize(Vector2f);
	static float vectorMath::vectorToAngle(Vector2f);
	static Vector2f vectorMath::limit(Vector2f, float);
	~vectorMath();
};


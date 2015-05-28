#pragma once
#include <SFML/Graphics.hpp>

class Triangles
{
public:
	sf::CircleShape Up;
	sf::CircleShape Down;
	void draw();
	void setPosition(float x, float y);
	int onMouseOver();
	Triangles(void);
	~Triangles(void);
};


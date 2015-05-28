#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>

class Obstacle
{
public:
	Obstacle(void);
	~Obstacle(void);
	void setRandomPosition();
	sf::RectangleShape shape;
	void draw();
private:
	sf::Texture *tx;
};


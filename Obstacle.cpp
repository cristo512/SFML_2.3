#include "Obstacle.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>


Obstacle::Obstacle(void)
{
	tx = new sf::Texture;
	tx = &globalGame->obstacleTextures.at(rand()%(globalGame->obstacleTextures.size()));
	shape.setSize(sf::Vector2f(tx->getSize().x, tx->getSize().y));
	shape.setTexture(tx);
	shape.setScale((rand()%2 == 0 ? 1 : -1) * 5,5);
}
void Obstacle::setRandomPosition()
{
	shape.setPosition(globalGame->window.getSize().x * 0.15 + (rand()%((int)(globalGame->window.getSize().x * 0.7) - (int)shape.getGlobalBounds().width)),
		rand()%(globalGame->window.getSize().y - (int)shape.getGlobalBounds().height));
}


Obstacle::~Obstacle(void)
{
}


void Obstacle::draw()
{
	globalGame->window.draw(shape);
}

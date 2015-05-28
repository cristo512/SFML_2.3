#include "Triangles.h"
#include "Game.h"

Triangles::Triangles(void)
{
	Up.setRadius(20);
	Up.setPointCount(3);
	Up.setFillColor(sf::Color::Red);
	Down.setRadius(20);
	Down.setPointCount(3);
	Down.setFillColor(sf::Color::Red);
	setPosition(globalGame->window.getSize().x/2,globalGame->window.getSize().y/2);
	Down.setScale(1, -1);
}


Triangles::~Triangles(void)
{
}

int Triangles::onMouseOver()
{
	int result = 0;
	if(globalGame->onMouseOver(Up))
	{
		Up.setFillColor(sf::Color::Green);
		result = 1;
	}
	else
		Up.setFillColor(sf::Color::Red);

	if(globalGame->onMouseOver(Down))
	{
		Down.setFillColor(sf::Color::Green);
		result = 2;
	}
	else
		Down.setFillColor(sf::Color::Red);

	return result;
}

void Triangles::setPosition(float x, float y)
{
	Up.setPosition(x, y - Up.getGlobalBounds().height - 5);
	Down.setPosition(x, y +  Down.getGlobalBounds().height + 5);
}
void Triangles::draw()
{
	globalGame->window.draw(Up);
	globalGame->window.draw(Down);
}
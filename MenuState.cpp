#include "MenuState.h"


MenuState::MenuState(void)
{
}
bool MenuState::init()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouseBlocked = true;
		mouseButtonWasPressed = true;
	}
	else
	{
		mouseBlocked = false;
		mouseButtonWasPressed = false;
	}

	text.init();
	
	text.addLine("Start");
	text.addLine("Options");
	text.addLine("Exit");


	return true;
}

void MenuState::checkEvents()
{
	if(mouseBlocked && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseBlocked = false;

	int mouseOnText = text.onMouseOver();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		globalGame->setState(play);

	if(mouseOnText != -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
	{
		if(mouseOnText == 0)
			globalGame->setState(play);
		else if(mouseOnText == 1)
			globalGame->setState(options);
		else if(mouseOnText == 2)
			globalGame->setState(END);
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
		mouseBlocked = true;
}

void MenuState::draw()
{
	globalGame->window.clear();
	text.draw();
	globalGame->window.display();
}

MenuState::~MenuState(void)
{
}

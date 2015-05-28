#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameState.h"
#include "Game.h"
#include "TextContainer.h"
#include "Triangles.h"
#include <sstream>

class Options : public gameState
{
public:
	Options(void);
	~Options(void);
	void draw();
	void checkEvents();
	bool init();
private:
	TextContainer text;
	Triangles triangles;
	sf::Text playersAmountText;
	std::ostringstream str;
	bool mouseBlocked;
	bool mouseButtonWasPressed;
};


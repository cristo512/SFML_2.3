#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameState.h"
#include "TextContainer.h"

class MenuState : public gameState
{
public:
	MenuState(void);
	~MenuState(void);
	void draw();
	void checkEvents();
	bool init();
private:
	TextContainer text;
	bool mouseBlocked;
	bool mouseButtonWasPressed;
};


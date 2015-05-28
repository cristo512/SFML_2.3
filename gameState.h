#pragma once
#include <SFML/Graphics.hpp>

class gameState
{
public:
	gameState(void);
	virtual ~gameState(void);
	virtual void draw() = 0;
	virtual void checkEvents() = 0;
	virtual bool init() = 0;
};


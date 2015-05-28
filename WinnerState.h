#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"

class WinnerState : public gameState
{
public:
	WinnerState(void);
	~WinnerState(void);
	bool init();
	void checkEvents();
	void draw();
private:
	sf::Text TheWinnerIs;
	sf::Text WhoIsTheWinner;
	bool spaceBlocked;
};


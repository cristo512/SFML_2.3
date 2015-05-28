#pragma once
#include "gameState.h"
#include "Triangles.h"
#include <SFML/Graphics.hpp>
#include "PlayerSettings.h"

class PlayerOptions : public gameState
{
public:
	PlayerOptions(void);
	~PlayerOptions(void);
	void draw();
	void checkEvents();
	bool init();
private:
	PlayerSettings newSettings;
	std::string *buttons;
	void next();
	bool mouseBlocked;
	void setButton(sf::Keyboard::Key key);
	int textAmount;
	int playerIt;
	int buttonsIt;
	Triangles triangles;
	bool drawTriangles;
	sf::Text *text;
	void setKeysStrings();
	std::string *keysString;
};


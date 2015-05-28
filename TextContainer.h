#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

class TextContainer
{
public:
	TextContainer();
	~TextContainer(void);
	void init();
	void addLine(std::string string);
	void draw();
	void setPosition(float x, float y);
	void setString(unsigned int it, std::string newText);
	void setColors(sf::Color mouseOn, sf::Color mouseOut);
	sf::Text getText(unsigned int it);
	int onMouseOver();
private:
	bool defaultSettings;
	void normalize();
	void update();
	sf::Font font;
	sf::Vector2f position;
	sf::Vector2f size;
	std::vector<sf::Text> text;
	sf::Color mouseOnColor;
	sf::Color mouseOutColor;
	float textSpace;
	float textHeight;
};


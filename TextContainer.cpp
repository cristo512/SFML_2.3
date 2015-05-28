#include "TextContainer.h"


void TextContainer::normalize()
{
	textHeight = 0;
	textSpace = 80.f;
}
void TextContainer::init()
{
	defaultSettings = true;
	position = sf::Vector2f(0,0);
	this->size = sf::Vector2f((float)globalGame->window.getSize().x, (float)globalGame->window.getSize().y);
	normalize();
}


void TextContainer::setPosition(float x, float y)
{
	defaultSettings = false;
	position.x = x;
	position.y = y;
	update();
}

TextContainer::TextContainer(void)
{
	mouseOnColor = sf::Color::Green;
	mouseOutColor = sf::Color::White;
}


TextContainer::~TextContainer(void)
{
}

void TextContainer::setColors(sf::Color mouseOn, sf::Color mouseOut)
{
	mouseOnColor = mouseOn;
	mouseOutColor = mouseOut;
}

void TextContainer::setString(unsigned int it, std::string newText)
{
	text[it].setString(newText);
	update();
};

int TextContainer::onMouseOver()
{
	for(unsigned int i = 0 ; i < text.size(); i++)
	{
		if(globalGame->onMouseOver(text.at(i)))
		{
			text.at(i).setColor(mouseOnColor);
			return i;
		}
		else
			text.at(i).setColor(mouseOutColor);
	}
	return -1;
}

void TextContainer::update()
{
	text[0].setPosition((size.x - text[0].getGlobalBounds().width)/2.f + position.x,
			(size.y - textHeight) / 2.f + position.y);


	for(unsigned int i = 1; i < text.size(); i++)
		text[i].setPosition((size.x - text[i].getGlobalBounds().width)/2.f + position.x,
			text[i-1].getPosition().y + text[i-1].getGlobalBounds().height + textSpace);	
}

void TextContainer::addLine(std::string string)
{
	text.push_back(sf::Text());
	text.at(text.size()-1).setFont(globalGame->font);
	text.at(text.size()-1).setString(string);
	text.at(text.size()-1).setColor(mouseOutColor);
	text.at(text.size()-1).setCharacterSize(72);
	textHeight += text.at(text.size()-1).getGlobalBounds().height + textSpace * (text.size() == 1 ? 0 : 1);

	update();
}

sf::Text TextContainer::getText(unsigned int it)
{
	return text.at(it);
}

void TextContainer::draw()
{
	for(unsigned int i = 0 ; i < text.size(); i++)
		globalGame->window.draw(text.at(i));
}
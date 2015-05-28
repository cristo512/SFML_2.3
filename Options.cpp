#include "Options.h"


Options::Options(void)
{
}
bool Options::init()
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

	text.setColors(sf::Color::Blue, sf::Color::Red);

	text.addLine("Players ");
	text.addLine("Menu");
	text.addLine("Quit");
	
	playersAmountText.setFont(globalGame->font);
	str.str("");
	str << globalGame->playerSettings.size();
	playersAmountText.setString(str.str());
	playersAmountText.setCharacterSize(72);
	playersAmountText.setColor(sf::Color::White);
	playersAmountText.setPosition(text.getText(0).getPosition().x + text.getText(0).getGlobalBounds().width + 40,
		text.getText(0).getPosition().y);


	
	triangles.setPosition(playersAmountText.getPosition().x + playersAmountText.getGlobalBounds().width + 50, 
		playersAmountText.getPosition().y + playersAmountText.getGlobalBounds().height);

	return true;
}


void Options::checkEvents()
{
	if(mouseBlocked && mouseButtonWasPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseBlocked = false;

	int mouseOnText = text.onMouseOver();
	int mouseOnTriangle = triangles.onMouseOver();

	if(mouseOnTriangle != 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
	{
		if(mouseOnTriangle == 1)
		{
			if(globalGame->playerSettings.size() == 1)
				globalGame->playerSettings.push_back (PlayerSettings(
					sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, 
					sf::Keyboard::Delete, sf::Keyboard::End, 
					sf::Keyboard::RControl));
			else if(globalGame->playerSettings.size() == 2)
				globalGame->playerSettings.push_back (PlayerSettings( 
					sf::Keyboard::U, sf::Keyboard::J, sf::Keyboard::H, sf::Keyboard::K, 
					sf::Keyboard::B, sf::Keyboard::N, 
					sf::Keyboard::M));
			else if(globalGame->playerSettings.size() == 3)
				globalGame->playerSettings.push_back (PlayerSettings( 
					sf::Keyboard::Numpad8, sf::Keyboard::Numpad5, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, 
					sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, 
					sf::Keyboard::Numpad0));
		}
		else if(mouseOnTriangle == 2)
			if(globalGame->playerSettings.size() > 1)
				globalGame->playerSettings.erase(globalGame->playerSettings.end()-1);

		str.str("");
		str << globalGame->playerSettings.size();
		playersAmountText.setString(str.str());

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
			mouseBlocked = true;
	}
	
	if(mouseOnText != -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
	{
		if(mouseOnText == 0)
			globalGame->setState(playerOptions);
		else if(mouseOnText == 1)
			globalGame->setState(menu);
		else if(mouseOnText == 2)
			globalGame->setState(END);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		globalGame->setState(play);
}

void Options::draw()
{
	globalGame->window.clear();
	text.draw();
	triangles.draw();
	globalGame->window.draw(playersAmountText);
	globalGame->window.display();
}


Options::~Options(void)
{
}

#include "WinnerState.h"
#include "Game.h"
#include <sstream>

WinnerState::WinnerState(void)
{
}


bool WinnerState::init()
{
	spaceBlocked = true;
	TheWinnerIs.setString("The Winner is:");
	std::ostringstream str;
	str << "Player " << globalGame->winnerID;
	WhoIsTheWinner.setString(str.str());
	if(globalGame->winnerID == -1)
		WhoIsTheWinner.setString("Nobody");

	TheWinnerIs.setCharacterSize(72);
	TheWinnerIs.setColor(sf::Color::Red);
	TheWinnerIs.setFont(globalGame->font);
	TheWinnerIs.setPosition((globalGame->window.getSize().x - TheWinnerIs.getGlobalBounds().width)/2.f,
		globalGame->window.getSize().y/4 - TheWinnerIs.getGlobalBounds().height/2.f);

	WhoIsTheWinner.setCharacterSize(72);
	WhoIsTheWinner.setColor(sf::Color::Red);
	WhoIsTheWinner.setFont(globalGame->font);
	WhoIsTheWinner.setPosition((globalGame->window.getSize().x - WhoIsTheWinner.getGlobalBounds().width)/2.f,
		globalGame->window.getSize().y*0.75 - WhoIsTheWinner.getGlobalBounds().height/2.f);
	return true;
}
void WinnerState::checkEvents()
{
	if(spaceBlocked && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		spaceBlocked = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spaceBlocked)
		globalGame->setState(play);
}
void WinnerState::draw()
{
	globalGame->window.clear();
	globalGame->window.draw(TheWinnerIs);
	globalGame->window.draw(WhoIsTheWinner);
	globalGame->window.display();
}

WinnerState::~WinnerState(void)
{
}

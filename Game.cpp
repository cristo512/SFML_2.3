#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "Options.h"
#include "PlayerOptions.h"
#include "WinnerState.h"
#include <string>
#include <sstream>

Game *globalGame;

bool Game::loadTextures()
{
	std::ostringstream str;
	int playersAmount = 4;
	playerTextures = new sf::Texture *[playersAmount];
	
	for(int i=0;i<playersAmount;i++)
	{
		playerTextures[i] = new sf::Texture [3];
		for(int j = 0; j < 3; j++)
		{
			str.str("");
			str << "./resources/Player ";
			str << i;
			str << "/pix";
			str << j;
			str << ".png";
			if(!playerTextures[i][j].loadFromFile(str.str()))
				return false;
		}
	}

	int i = 0;
	do
	{
		obstacleTextures.push_back(sf::Texture());
		str.str("");
		str << "./resources/Obstacles/obstacle";
		str << i;
		str << ".png";
	}while(obstacleTextures[i++].loadFromFile(str.str()));

	obstacleTextures.erase(obstacleTextures.end() - 1);

	if(!bgTexture.loadFromFile("./resources/background.png")
		|| !bulletTexture.loadFromFile("./resources/bullet.png")
		|| !font.loadFromFile("./resources/sansation.ttf"))
		return false;
	return true;
}
void Game::setState(StateEnum newState)
{
	if(currentState != newState)
	{
		if(currentState != BEGIN)
			delete state;
		currentState = newState;
		switch(currentState)
		{
			case play:
				state = new PlayState;
				break;
			case options:
				state = new Options;
				break;
			case menu:
				state = new MenuState;
				break;
			case playerOptions:
				state = new PlayerOptions;
				break;
			case winner:
				state = new WinnerState;
				break;
			case END:
				window.close();
				break;
		}
		if(currentState != END)
			if(!state->init())
				std::cout<<"to problem";
	}
}

bool Game::Init()
{
	srand(time(NULL));

	sf::VideoMode Mode = sf::VideoMode::getDesktopMode();

    window.create(sf::VideoMode(Mode.width, Mode.height, 32), "Radius",
                            sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
	
	//window.setFrameLimit(100);

	if(!loadTextures())
		return false;

	winnerID = -1;

	playerSettings.push_back (PlayerSettings( 
		sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, 
		sf::Keyboard::Z, sf::Keyboard::X, 
		sf::Keyboard::Space));

	playerSettings.push_back (PlayerSettings(
		sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, 
		sf::Keyboard::Delete, sf::Keyboard::End, 
		sf::Keyboard::RControl));

	
	currentState = BEGIN;

	setState(menu);

	return true;
}


Game::Game(void)
{
	globalGame = this;
}


void Game::checkEvents()
{
    if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Escape)
		{
			if(currentState == menu)
				window.close();
			else
				setState(menu);
		}
	}
    if(event.type == sf::Event::Closed)
        window.close();
}

int Game::Run()
{
	while(window.isOpen())
    {
		
		deltaTime = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();
	
		state->draw();
		state->checkEvents();

        while(window.pollEvent(event))
			checkEvents();
    }
	return EXIT_SUCCESS;
}

Game::~Game(void)
{
}

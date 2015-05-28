#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include "PlayerSettings.h"

enum StateEnum
{
	BEGIN,
	play,
	options,
	menu,
	playerOptions,
	winner,
	END
};

struct AttackInfo
{
	int direction;
	int y;
	sf::Vector2f startPosition;
	float scale;
};

class Game
{
public:
	Game(void);
	~Game(void);
	bool Init();
	int Run();
	bool loadTextures();
	void checkEvents();
	void setState(StateEnum newState);
	template <class T>
	bool onMouseOver(T shape)
	{
		return shape.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
	}
	sf::RenderWindow window;
	sf::Texture bulletTexture;
	sf::Texture bgTexture;
	std::vector<sf::Texture> obstacleTextures;
	sf::Texture **playerTextures;
	gameState *state;
    sf::Event event;
    sf::Clock deltaClock;
	sf::Font font;
	std::vector<PlayerSettings> playerSettings;

	sf::IntRect FToIRect(const sf::FloatRect& f)
	{
		return sf::IntRect((int) f.left, (int) f.top, (int) f.width, (int) f.height);
	};

	template<class T1, class T2>
	bool isCollision(T1 a, T2 b)
	{	
		sf::Image imgA;
		sf::Image imgB;

		if(a.getTexture() == NULL)
			imgA.create(a.getGlobalBounds().width, a.getGlobalBounds().height, sf::Color::Red);
		else
			imgA = a.getTexture()->copyToImage();

		if(b.getTexture() == NULL)
			imgB.create(b.getGlobalBounds().width, b.getGlobalBounds().height, sf::Color::Red);
		else
			imgB = b.getTexture()->copyToImage();
		
		if(a.getGlobalBounds().width == 0 || a.getGlobalBounds().height == 0)
			return false;
		if(b.getGlobalBounds().width == 0 || b.getGlobalBounds().height == 0)
			return false;


		sf::IntRect boundsA(FToIRect(a.getGlobalBounds()));
		sf::IntRect boundsB(FToIRect(b.getGlobalBounds()));
		sf::IntRect intersection;

		if(boundsA.intersects(boundsB, intersection)) {
			const sf::Transform& inverseA(a.getInverseTransform());
			const sf::Transform& inverseB(b.getInverseTransform());

			const sf::Vector2u& sizeA(imgA.getSize());
			const sf::Vector2u& sizeB(imgB.getSize());

			const sf::Uint8* pixA = imgA.getPixelsPtr();
			const sf::Uint8* pixB = imgB.getPixelsPtr();

			sf::Vector2f vecA, vecB;
			int xMax = intersection.left + intersection.width;
			int yMax = intersection.top + intersection.height;

			for(int x = intersection.left; x < xMax; x++)
				for(int y = intersection.top; y < yMax; y++)
				{
					vecA = inverseA.transformPoint(x, y);
					vecB = inverseB.transformPoint(x, y);

					int idxA = ((int) vecA.x + ((int) vecA.y)*sizeA.x)*4 + 3;
					int idxB = ((int) vecB.x + ((int) vecB.y)*sizeB.x)*4 + 3;

					if(vecA.x > 0 && vecA.y > 0 &&
							vecB.x > 0 && vecB.y > 0 &&
							vecA.x < sizeA.x && vecA.y < sizeA.y &&
							vecB.x < sizeB.x && vecB.y < sizeB.y &&
							pixA[idxA] > 0 &&
							pixB[idxB] > 0) {
						return true;
					}
				}
		}

		return false;
	};

	float deltaTime;
	int winnerID;
private:
	StateEnum currentState;
};

extern Game* globalGame;
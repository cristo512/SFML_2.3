#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "PlayerSettings.h"
#include "Obstacle.h"
#include <iostream>
#include <vector>

class Player
{
public:
	Player(PlayerSettings settings);
	~Player(void);
	void checkEvents(std::vector<Obstacle> obstacles);
	void draw();
	void setMoveKeys(sf::Keyboard::Key Up, sf::Keyboard::Key Down, 
		sf::Keyboard::Key Left, sf::Keyboard::Key Right);
	void setSizeKeys(sf::Keyboard::Key Bigger, sf::Keyboard::Key Smaller);
	void changeDirection();
	void setAttackKey(sf::Keyboard::Key Attack);
	AttackInfo attackInfo;
	bool isAttacking;
	bool isPreparing;
	void setTextures(sf::Texture *texture);
	bool gotShreckt(float amount);
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
	void setSize(char size); // s - small, n - normal, b - big
	template<class T>
	bool isCollision(T b)
	{
		return globalGame->isCollision(sprite, b);
	};
	unsigned int ID;
private:
	void prepare();
	void move(std::vector<Obstacle> obstacles);
	void changeSize(std::vector<Obstacle> obstacles);
	void setTexture(int tx);
	void changeTexture();
	void checkPosition();
	void attack();
	void setHP();
	void changeHP();
	bool canAttack;
	bool canBeBigger;
	char size;
	char previousSize;
	sf::Clock moveClock;
	sf::Clock attackClock;
	sf::Clock sizeClock;
	sf::Sprite sprite;
	sf::Texture *texture;
	sf::RectangleShape hpWhite;
	sf::RectangleShape hpColor;
	sf::Color defaultColor;
	int currentTexture;
	int direction;
	float hp;
	float scale;
	float defaultScale;
	float speed;
	float changeSizeSpeed;
	sf::Keyboard::Key Up;
	sf::Keyboard::Key Down;
	sf::Keyboard::Key Left;
	sf::Keyboard::Key Right;
	sf::Keyboard::Key Bigger;
	sf::Keyboard::Key Smaller;
	sf::Keyboard::Key Attack;
};


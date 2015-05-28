#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"


class Bullet
{
public:
	Bullet();
	~Bullet(void);
	sf::Sprite sprite;
	float createdTime;
	void move();
	void draw();
	void init(AttackInfo &attackInfo, float createdTime);
	bool canDestroy();
	float dmg;
	int untouchablePlayer;
private:
	sf::Texture texture;
	int speed;
	int scaling;
	float rotationSpeed;
	float y;
	int direction;
};


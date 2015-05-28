#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "gameState.h"
#include "Player.h"
#include "Bullet.h"
#include "Obstacle.h"

class PlayState : public gameState
{
public:
	PlayState(void);
	~PlayState(void);
	void draw();
	void checkEvents();
	bool init();
private:
	void addBullet(AttackInfo attackInfo, unsigned int &player);
	void playersBehavior();
	void bulletsBehavior();
	int state;
	std::vector<Player> player;
	std::vector<Bullet> bullet;
	std::vector<Obstacle> obstacle;
	sf::Clock mainClock;
    sf::Color clearColor;
	bool toDestroy;

};


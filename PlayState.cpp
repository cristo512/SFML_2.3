#include "PlayState.h"
#include <iostream>

PlayState::PlayState(void)
{
	clearColor = sf::Color(0,150,0);
}

bool PlayState::init()
{
	state = 0;

	for(unsigned int i = 0 ; i < globalGame->playerSettings.size(); i++)
	{
		player.push_back(Player(globalGame->playerSettings.at(i)));
		player.at(i).setTextures(globalGame->playerTextures[i]);
		player.at(i).ID = i;
	}
	
	
	if(globalGame->playerSettings.size() >= 1)
	{
		player.at(0).setPosition(sf::Vector2f(0, (float)globalGame->window.getSize().y/2.f));
		player.at(0).changeDirection();
	}
	if(globalGame->playerSettings.size() >= 2)
		player.at(1).setPosition(sf::Vector2f((float)globalGame->window.getSize().x, (float)globalGame->window.getSize().y/2.f));
	if(globalGame->playerSettings.size() >= 3)
	{
		player.at(2).setPosition(sf::Vector2f(0, (float)globalGame->window.getSize().y/5.f));
		player.at(2).changeDirection();
	}
	if(globalGame->playerSettings.size() == 4)
		player.at(3).setPosition(sf::Vector2f((float)globalGame->window.getSize().x, (float)globalGame->window.getSize().y/5.f));
	
	for(int i = 0 ; i < 1 + rand()%4; i++)
		obstacle.push_back(Obstacle());

	for(unsigned int i = 0 ; i < obstacle.size(); i++)
	{
		while(true)
		{
			bool toBreak = true;
			obstacle[i].setRandomPosition();
			for(unsigned int j = 0 ; j < player.size(); j++)
				if(player[j].isCollision(obstacle[i].shape))
					toBreak = false;
			for(unsigned int j = 0 ; j < obstacle.size(); j++)
				if(globalGame->isCollision(obstacle[i].shape, obstacle[j].shape))
					if(i != j)
						toBreak = false;
			if(toBreak)
				break;
		}
	}
	return true;
}

void PlayState::playersBehavior()
{
	for(unsigned int i = 0 ; i < player.size(); i++)
	{
		player.at(i).checkEvents(obstacle);
		if(!player.at(i).isPreparing && player.at(i).isAttacking)
		{
			addBullet(player.at(i).attackInfo, player.at(i).ID);
			player.at(i).isAttacking = false;
		}
	}
}
void PlayState::bulletsBehavior()
{
	for(unsigned int i = 0 ; i < bullet.size() ; i++)
	{
		toDestroy = false;
		bullet.at(i).move();
		
		float bulletTime = mainClock.getElapsedTime().asSeconds() - bullet.at(i).createdTime;

		for(unsigned int j = 0 ; j < player.size(); j++)
		{
			if(player.at(j).ID == bullet.at(i).untouchablePlayer && bulletTime < 1.f)
				continue;
			else if(player.at(j).isCollision(bullet.at(i).sprite))
			{
				toDestroy = true;
				player.at(j).setSize(rand()%2 == 0? 'b' : 's');
				if(!player.at(j).gotShreckt(bullet.at(i).dmg))
					player.erase(player.begin()+j);
			}
		}
		if(bullet.at(i).canDestroy())
			toDestroy = true;
		else if(bulletTime > 10.f)
			toDestroy = true;
		else
			for(unsigned int j = 0 ; j < obstacle.size(); j++)
				if(globalGame->isCollision(obstacle[j].shape, bullet[i].sprite))
					toDestroy = true;
		if(toDestroy)
			bullet.erase(bullet.begin() + i);
	}
	if(player.size() < 2)
	{
		if(player.size() == 1 && globalGame->playerSettings.size() != 1)
		{
			globalGame->winnerID = player[0].ID + 1;
			globalGame->setState(winner);
		}
		if(player.size() == 0)
		{
			globalGame->winnerID = -1;
			globalGame->setState(winner);
		}
	}
}

void PlayState::addBullet(AttackInfo attackInfo, unsigned int &player)
{
	bullet.push_back(Bullet());
	bullet.at(bullet.size()-1).init(attackInfo, mainClock.getElapsedTime().asSeconds());
	bullet.at(bullet.size()-1).untouchablePlayer = player;
}

PlayState::~PlayState(void)
{
}

void PlayState::checkEvents()
{
	playersBehavior();
	bulletsBehavior();
}

void PlayState::draw()
{
    globalGame->window.clear(clearColor);
	for(unsigned int i = 0 ; i < player.size() ; i++)
		player.at(i).draw();
	for(unsigned int i = 0 ; i < bullet.size() ; i++)
		bullet.at(i).draw();
	for(unsigned int i = 0 ; i < obstacle.size() ; i++)
		obstacle.at(i).draw();
    globalGame->window.display();
}

#include "Bullet.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

Bullet::Bullet()
{

}
void Bullet::init(AttackInfo &attackInfo, float createdTime)
{
	sprite.setTexture(globalGame->bulletTexture);
	sprite.setPosition(attackInfo.startPosition);
	this->createdTime = createdTime;

	this->direction = (attackInfo.direction * -1);
	attackInfo.scale *= 0.8f;
	sprite.setScale(this->direction * attackInfo.scale * 0.6, attackInfo.scale * 0.6);
	if(attackInfo.scale < 2)
		dmg = 5;
	if(attackInfo.scale < 4)
		dmg = 8;
	else
		dmg = 10;
	
	speed = 110 * attackInfo.scale;
	y = (globalGame->window.getSize().y / 3) / (globalGame->window.getSize().y / speed);
	y *= attackInfo.y;
	rotationSpeed = (10 + rand()%70)/10.f;
}

bool Bullet::canDestroy()
{
	if(sprite.getPosition().x < 0 || sprite.getPosition().x > globalGame->window.getSize().x)
		return true;
	return false;
}

void Bullet::move()
{
	sprite.move(direction * globalGame->deltaTime * speed, y * globalGame->deltaTime);
	sprite.setRotation(sprite.getRotation() + (rotationSpeed * direction));
}


Bullet::~Bullet(void)
{
}

void Bullet::draw()
{
	globalGame->window.draw(sprite);
}

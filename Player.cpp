#include "Player.h"

void Player::changeHP()
{
	hpWhite.setScale(scale, scale);
	hpWhite.setPosition(sprite.getPosition().x + ((direction == 1 ? sprite.getGlobalBounds().width * 0.12f : -sprite.getGlobalBounds().width * 0.12f - hpWhite.getGlobalBounds().width)) ,
						sprite.getPosition().y - 2 * hpWhite.getGlobalBounds().height);
	if(hpWhite.getPosition().y < 0)
		hpWhite.setPosition(hpWhite.getPosition().x, 
		sprite.getPosition().y + sprite.getGlobalBounds().height + hpWhite.getGlobalBounds().height);

	hpColor.setScale(hp/100.f * scale, scale);
	hpColor.setPosition(hpWhite.getPosition());
}

void Player::setHP()
{
	hpWhite.setSize(sf::Vector2f(sprite.getGlobalBounds().width * 0.6f, 2));
	hpWhite.setFillColor(sf::Color::White);

	hpColor.setSize(sf::Vector2f(sprite.getGlobalBounds().width * 0.6f, 2));
	hpColor.setFillColor(sf::Color::Green);
}

void Player::setTextures(sf::Texture *texture)
{
	this->texture = texture;
	currentTexture = 0;
	sprite.setTexture(texture[currentTexture]);
	setHP();
    sprite.setScale(scale, scale);
	sprite.setPosition(globalGame->window.getSize().y/2 - sprite.getGlobalBounds().width/2, 
		globalGame->window.getSize().y/2 - sprite.getGlobalBounds().height/2);
	changeHP();
}
Player::Player(PlayerSettings settings)
{
	defaultScale = 3;
	scale = defaultScale;
	size = 'n';
	hp = 100;
	direction = 1;
	speed = 50;
	changeSizeSpeed = 3.f;
	isAttacking = false;
	isPreparing = false;
	canAttack = true;
	
	setMoveKeys(settings.Up, 
			settings.Down, 
			settings.Left, 
			settings.Right);
	setSizeKeys(settings.Bigger, 
			settings.Smaller);
	setAttackKey(settings.Attack);

	defaultColor = sprite.getColor();
}

void Player::setMoveKeys(sf::Keyboard::Key Up, sf::Keyboard::Key Down, 
		sf::Keyboard::Key Left, sf::Keyboard::Key Right)
{
	this->Up = Up;
	this->Down = Down;
	this->Left = Left;
	this->Right = Right;
}
void Player::setSizeKeys(sf::Keyboard::Key Bigger, sf::Keyboard::Key Smaller)
{
	this->Bigger = Bigger;
	this->Smaller = Smaller;
}
void Player::setAttackKey(sf::Keyboard::Key Attack)
{
	this->Attack = Attack;
}

void Player::setTexture(int tx)
{
	sprite.setTexture(texture[tx]);
	currentTexture = tx;
}

void Player::changeTexture()
{
	if(currentTexture == 0)
		currentTexture = 1;
	else
		currentTexture = 0;
	setTexture(currentTexture);
}

void Player::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
	checkPosition();
	changeHP();
}
void Player::checkPosition()
{    
	if(sprite.getPosition().y + sprite.getGlobalBounds().height > globalGame->window.getSize().y)
        sprite.setPosition(sprite.getPosition().x,
                            globalGame->window.getSize().y - sprite.getGlobalBounds().height);
	if(sprite.getPosition().y < 0)
		sprite.setPosition(sprite.getPosition().x, 0);

    if(sprite.getPosition().x + (sprite.getGlobalBounds().width * (direction == 1 ? 1 : 0)) > globalGame->window.getSize().x)
        sprite.setPosition(globalGame->window.getSize().x - (sprite.getGlobalBounds().width * (direction == 1 ? 1 : 0)), 
		sprite.getPosition().y);

	if( sprite.getPosition().x - (sprite.getGlobalBounds().width * (direction == 1 ? 0 : 1)) < 0 )
		sprite.setPosition(sprite.getGlobalBounds().width * (direction == 1 ? 0 : 1), sprite.getPosition().y);

}

void Player::setSize(char size)
{
	previousSize = this->size;
	this->size = size;
	sizeClock.restart();
}

void Player::changeSize(std::vector<Obstacle> obstacles)
{
	float middleX = sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) * (direction == 1? 1 : -1);
	float middleY = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
	
	if(size == 'n' )
	{
		if(scale >= defaultScale && previousSize == 'b')
			scale -= changeSizeSpeed * globalGame->deltaTime;

		else if(scale <= defaultScale && previousSize == 's')
			scale += changeSizeSpeed * globalGame->deltaTime;
	}

	if( size == 's' )
		if(scale >= defaultScale / 2.f)
			scale -= changeSizeSpeed * globalGame->deltaTime;

	if ( size == 'b' && canBeBigger)
		if(scale <= defaultScale * 2)
			scale += changeSizeSpeed * globalGame->deltaTime;
	
	for(int i = 0 ; i < obstacles.size();i++)
		if(isCollision(obstacles[i].shape) && (size == 'b' || (size =='n' && previousSize == 's') ) && scale > defaultScale / 2.f)
		{
			scale -= changeSizeSpeed * globalGame->deltaTime;
			canBeBigger = false;
		}
		else
			canBeBigger = true;

	sprite.setScale(direction * scale, scale);
	sprite.setPosition( middleX + (sprite.getGlobalBounds().width / 2) * (direction == 1? -1 : 1),
		middleY - sprite.getGlobalBounds().height / 2);
}

void Player::attack()
{
	if(canAttack)
	{
		canAttack = false;
		attackClock.restart();
		isAttacking = true;
		isPreparing = true;

		if(sf::Keyboard::isKeyPressed(Down))
			attackInfo.y = 1;
		else if(sf::Keyboard::isKeyPressed(Up))
			attackInfo.y = -1;
		else
			attackInfo.y = 0;
	}
}
void Player::prepare()
{
	if(attackClock.getElapsedTime().asSeconds() > 0.3)
	{
		isPreparing = false;
		attackInfo.direction = direction;
		attackInfo.startPosition = sf::Vector2f(sprite.getPosition().x + (sprite.getGlobalBounds().width / 6) * (direction == 1? 1 : -1),
									sprite.getPosition().y + sprite.getGlobalBounds().height / 6);
		
		if(sf::Keyboard::isKeyPressed(Down))
			attackInfo.y = 1;
		else if(sf::Keyboard::isKeyPressed(Up))
			attackInfo.y = -1;

		attackInfo.scale = scale;
		currentTexture = 0;
	}
	else if(attackClock.getElapsedTime().asSeconds() > 0.1)
		sprite.setTexture(texture[2]);
}

void Player::checkEvents(std::vector<Obstacle> obstacles)
{
	sprite.setColor(defaultColor);
	
	if( (size == 's' || size == 'b') && sizeClock.getElapsedTime().asSeconds() > 5.f )
		setSize('n');
	if(attackClock.getElapsedTime().asSeconds() > 0.5)
		canAttack = true;
	if(isPreparing)
		prepare();
	else
	{
		if(sf::Keyboard::isKeyPressed(Attack))
			attack();
		if(sf::Keyboard::isKeyPressed(Up)
			|| sf::Keyboard::isKeyPressed(Down)
			|| sf::Keyboard::isKeyPressed(Left)
			|| sf::Keyboard::isKeyPressed(Right))
			move(obstacles);
		else
			setTexture(0);
		if(sf::Keyboard::isKeyPressed(Bigger) && size == 'n')
			setSize('b');
		if(sf::Keyboard::isKeyPressed(Smaller) && size == 'n')
			setSize('s');
		changeSize(obstacles);
	}
	checkPosition();
	changeHP();
}

void Player::move(std::vector<Obstacle> obstacles)
{
    if(moveClock.getElapsedTime().asSeconds() > 0.3)
    {
        changeTexture();
        moveClock.restart();
    }
	if(sf::Keyboard::isKeyPressed(Up))
	{
        sprite.move(0.f, -speed * (scale / 1) * globalGame->deltaTime);
		for(int i = 0 ; i < obstacles.size() ; i++)
			if(isCollision(obstacles[i].shape))
				sprite.move(0.f, speed * (scale / 1) * globalGame->deltaTime);
	}
    if(sf::Keyboard::isKeyPressed(Down))
	{
        sprite.move(0.f, speed * (scale / 1) * globalGame->deltaTime);
		for(int i = 0 ; i < obstacles.size() ; i++)
			if(isCollision(obstacles[i].shape))
				sprite.move(0.f, -speed * (scale / 1) * globalGame->deltaTime);
	}
    if(sf::Keyboard::isKeyPressed(Left))
    {
        if(!sf::Keyboard::isKeyPressed(Right) && direction == -1)
        {
            direction = 1;
            sprite.move(-sprite.getGlobalBounds().width,0);
        }
        sprite.move(-speed * (scale / 1) * globalGame->deltaTime, 0.f);
		for(int i = 0 ; i < obstacles.size() ; i++)
			if(isCollision(obstacles[i].shape))
				sprite.move(speed * (scale / 1) * globalGame->deltaTime, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(Right))
    {
        if(!sf::Keyboard::isKeyPressed(Left) && direction == 1)
        {
            direction = -1;
            sprite.move(sprite.getGlobalBounds().width,0);
        }
        sprite.move(speed * (scale / 1) * globalGame->deltaTime, 0.f);
		for(int i = 0 ; i < obstacles.size() ; i++)
			if(isCollision(obstacles[i].shape))
				sprite.move(-speed * (scale / 1) * globalGame->deltaTime, 0.f);
    }
    sprite.setScale(direction * scale, scale);
}

void Player::setColor(sf::Color color)
{
	sprite.setColor(color);
}

void Player::changeDirection()
{
    if(direction == -1)
    {
        direction = 1;
        sprite.move(-sprite.getGlobalBounds().width,0);
    }
    if(direction == 1)
    {
        direction = -1;
        sprite.move(sprite.getGlobalBounds().width,0);
    }
	sprite.setScale(direction * scale, scale);
}

bool Player::gotShreckt(float amount)
{
	sprite.setColor(sf::Color::Red);
	hp = (hp - amount);
	if(hp<=0)
		return false;
	changeHP();
	return true;
}

void Player::draw()
{
	globalGame->window.draw(sprite);
	globalGame->window.draw(hpWhite);
	globalGame->window.draw(hpColor);
}

Player::~Player(void)
{
}

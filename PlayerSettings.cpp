#include "PlayerSettings.h"

PlayerSettings::PlayerSettings()
{

}

PlayerSettings::PlayerSettings(sf::Keyboard::Key Up,
	sf::Keyboard::Key Down,
	sf::Keyboard::Key Left,
	sf::Keyboard::Key Right,
	sf::Keyboard::Key Bigger,
	sf::Keyboard::Key Smaller,
	sf::Keyboard::Key Attack)
	{
		this->Up = Up;
		this->Down = Down;
		this->Left = Left;
		this->Right = Right;
		this->Bigger = Bigger;
		this->Smaller = Smaller;
		this->Attack = Attack;
	}


PlayerSettings::~PlayerSettings(void)
{
}

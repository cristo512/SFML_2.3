#pragma once
#include <SFML/Graphics.hpp>
class PlayerSettings
{
public:
	PlayerSettings();
	PlayerSettings(sf::Keyboard::Key Up,
	sf::Keyboard::Key Down,
	sf::Keyboard::Key Left,
	sf::Keyboard::Key Right,
	sf::Keyboard::Key Bigger,
	sf::Keyboard::Key Smaller,
	sf::Keyboard::Key Attack);
	~PlayerSettings();
	sf::Keyboard::Key Up;
	sf::Keyboard::Key Down;
	sf::Keyboard::Key Left;
	sf::Keyboard::Key Right;
	sf::Keyboard::Key Bigger;
	sf::Keyboard::Key Smaller;
	sf::Keyboard::Key Attack;
};

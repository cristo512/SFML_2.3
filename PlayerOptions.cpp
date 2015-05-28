#include "PlayerOptions.h"
#include "Game.h"
#include <sstream>


PlayerOptions::PlayerOptions(void)
{
}

bool PlayerOptions::init()
{
	keysString = new std::string [(int)sf::Keyboard::KeyCount];
	setKeysStrings();
	mouseBlocked = true;
	textAmount = 4;
	playerIt = 0;
	text = new sf::Text [textAmount];
	text[0].setString("Options");
	text[1].setString("Choose Player: ");
	text[2].setString("1");
	text[3].setString("Next");
	for(int i = 0 ; i < textAmount; i++)
	{
		text[i].setFont(globalGame->font);
		text[i].setCharacterSize(62);
		text[i].setColor(sf::Color::White);
	}
	text[0].setPosition(30, globalGame->window.getSize().y - 50 - text[0].getGlobalBounds().height);
	text[1].setPosition(globalGame->window.getSize().x / 2 - text[1].getGlobalBounds().width - 30
		, globalGame->window.getSize().y / 4);
	text[2].setPosition(globalGame->window.getSize().x / 2 + 30,
		globalGame->window.getSize().y / 4);
	text[3].setPosition(globalGame->window.getSize().x - 30 - text[3].getGlobalBounds().width, globalGame->window.getSize().y - 50 - text[3].getGlobalBounds().height);
	triangles.setPosition(text[2].getPosition().x + text[2].getGlobalBounds().width + 50, text[2].getPosition().y + text[2].getGlobalBounds().height);
	
	buttonsIt = -1;

	buttons = new std::string [7];
	
	buttons[0] = "Up";
	buttons[1] = "Down";
	buttons[2] = "Left";
	buttons[3] = "Right";
	buttons[4] = "Bigger";
	buttons[5] = "Smaller";
	buttons[6] = "Attack";

	drawTriangles = true;

	return true;
}

void PlayerOptions::next()
{
	if(buttonsIt == -1)
	{
		newSettings = globalGame->playerSettings[playerIt];
		drawTriangles = false;
	}
	if(++buttonsIt == 7)
	{
		globalGame->playerSettings[playerIt] = newSettings;
		globalGame->setState(options);
	}
	else
	{
		if(text[2].getString() != "")
		{
			text[1].setString(buttons[buttonsIt]);
			text[2].setString("");
			
			switch(buttonsIt)
			{
				case 0:
					text[2].setString(keysString[newSettings.Up]);
					break;
				case 1:
					text[2].setString(keysString[newSettings.Down]);
					break;
				case 2:
					text[2].setString(keysString[newSettings.Left]);
					break;
				case 3:
					text[2].setString(keysString[newSettings.Right]);
					break;
				case 4:
					text[2].setString(keysString[newSettings.Bigger]);
					break;
				case 5:
					text[2].setString(keysString[newSettings.Smaller]);
					break;
				case 6:
					text[2].setString(keysString[newSettings.Attack]);
					break;
			}
		}
		else
			buttonsIt--;
	}
}

void PlayerOptions::setButton(sf::Keyboard::Key key)
{
	switch(buttonsIt)
	{
		case 0:
			newSettings.Up = key;
			break;
		case 1:
			newSettings.Down = key;
			break;
		case 2:
			newSettings.Left = key;
			break;
		case 3:
			newSettings.Right = key;
			break;
		case 4:
			newSettings.Bigger = key;
			break;
		case 5:
			newSettings.Smaller = key;
			break;
		case 6:
			newSettings.Attack = key;
			break;
	}
}

void PlayerOptions::checkEvents()
{
	if(mouseBlocked && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseBlocked = false;

	for(int button = sf::Keyboard::A ; button < sf::Keyboard::KeyCount ; button++)
	{
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)button))
		{
			std::ostringstream str;
			str.str("");
			//str << (char)('A' + (char)(button));
			str << keysString[(sf::Keyboard::Key)button];
			text[2].setString(str.str());
			setButton((sf::Keyboard::Key)button);
		}
	}


	if(drawTriangles)
	{
		int mouseOnTriangle = triangles.onMouseOver();
		if(!mouseBlocked && mouseOnTriangle == 1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && playerIt < globalGame->playerSettings.size()-1)
			playerIt++;
		if(!mouseBlocked && mouseOnTriangle == 2 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && playerIt > 0)
			playerIt--;
	
		std::ostringstream str;
		str.str("");
		str << playerIt + 1;
		text[2].setString(str.str());
	}

	for(int i = 0 ; i < textAmount; i++)
		if(globalGame->onMouseOver(text[i]))
		{
			text[i].setColor(sf::Color::Green);
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
			{
				if(i == 0)
					globalGame->setState(options);
				if(i == 2)
					sf::Keyboard::setVirtualKeyboardVisible(true);
				if(i == 3)
					next();
				break;
			}
		}
		else
			text[i].setColor(sf::Color::White);
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseBlocked)
		mouseBlocked = true;

}

PlayerOptions::~PlayerOptions(void)
{
}


void PlayerOptions::draw()
{
	globalGame->window.clear();
	for( int i = 0 ; i < textAmount ; i++)
		globalGame->window.draw(text[i]);
	if(drawTriangles)
		triangles.draw();
	globalGame->window.display();
}

void PlayerOptions::setKeysStrings()
{
	keysString[sf::Keyboard::A] = "A";	
	keysString[sf::Keyboard::B] = "B";
	keysString[sf::Keyboard::C] = "C";
	keysString[sf::Keyboard::D] = "D";
	keysString[sf::Keyboard::E] = "E";
	keysString[sf::Keyboard::F] = "F";
	keysString[sf::Keyboard::G] = "G";
	keysString[sf::Keyboard::H] = "H";
	keysString[sf::Keyboard::I] = "I";
	keysString[sf::Keyboard::J] = "J";
	keysString[sf::Keyboard::K] = "K";
	keysString[sf::Keyboard::L] = "L";
	keysString[sf::Keyboard::M] = "M";
	keysString[sf::Keyboard::N] = "N";
	keysString[sf::Keyboard::O] = "O";
	keysString[sf::Keyboard::P] = "P";
	keysString[sf::Keyboard::R] = "R";
	keysString[sf::Keyboard::S] = "S";
	keysString[sf::Keyboard::T] = "T";
	keysString[sf::Keyboard::U] = "U";
	keysString[sf::Keyboard::V] = "V";
	keysString[sf::Keyboard::W] = "W";
	keysString[sf::Keyboard::X] = "X";
	keysString[sf::Keyboard::Y] = "Y";
	keysString[sf::Keyboard::Z] = "Z";
	
	keysString[sf::Keyboard::Num0] = "0";
	keysString[sf::Keyboard::Num1] = "1";
	keysString[sf::Keyboard::Num2] = "2";
	keysString[sf::Keyboard::Num3] = "3";
	keysString[sf::Keyboard::Num4] = "4";
	keysString[sf::Keyboard::Num5] = "5";
	keysString[sf::Keyboard::Num6] = "6";
	keysString[sf::Keyboard::Num7] = "7";
	keysString[sf::Keyboard::Num8] = "8";
	keysString[sf::Keyboard::Num9] = "9";
	
	keysString[sf::Keyboard::Escape] = "Escape";

	keysString[sf::Keyboard::LControl] = "LControl";
	keysString[sf::Keyboard::LShift] = "LShift";
	keysString[sf::Keyboard::LAlt] = "LAlt";
	keysString[sf::Keyboard::LSystem] = "LSystem";
	
	keysString[sf::Keyboard::RControl] = "RControl";
	keysString[sf::Keyboard::RShift] = "RShift";
	keysString[sf::Keyboard::RAlt] = "RAlt";
	keysString[sf::Keyboard::RSystem] = "RSystem";
	
	keysString[sf::Keyboard::Menu] = "Menu";
	
	keysString[sf::Keyboard::RBracket] = "The ] key";
	keysString[sf::Keyboard::LBracket] = "The [ key";

	
	keysString[sf::Keyboard::SemiColon] = "The ; key";
	keysString[sf::Keyboard::Comma] = "The , key";
	keysString[sf::Keyboard::Period] = "The . key";
	keysString[sf::Keyboard::Quote] = "The ' key";
	
	keysString[sf::Keyboard::Slash] = "The / key";
	keysString[sf::Keyboard::BackSlash] = "The \ key";
	keysString[sf::Keyboard::Tilde] = "The ~ key";
	keysString[sf::Keyboard::Equal] = "The = key";
	keysString[sf::Keyboard::Dash] = "The - key";
	keysString[sf::Keyboard::Space] = "Space";
	
	keysString[sf::Keyboard::BackSpace] = "BackSpace";
	keysString[sf::Keyboard::Tab] = "Tabulation";
	keysString[sf::Keyboard::PageUp] = "Page up";
	keysString[sf::Keyboard::PageDown] = "Page down";
	keysString[sf::Keyboard::End] = "End";
	keysString[sf::Keyboard::Home] = "Home";
	keysString[sf::Keyboard::Insert] = "Insert";
	keysString[sf::Keyboard::Delete] = "Delete";

	keysString[sf::Keyboard::Add] = "+";
	keysString[sf::Keyboard::Subtract] = "-";
	keysString[sf::Keyboard::Multiply] = "*";
	keysString[sf::Keyboard::Divide] = "/";
	
	keysString[sf::Keyboard::Left] = "Left";
	keysString[sf::Keyboard::Right] = "Right";
	keysString[sf::Keyboard::Up] = "Up";
	keysString[sf::Keyboard::Down] = "Down";
	
	keysString[sf::Keyboard::Numpad0] = "Numpad 0";
	keysString[sf::Keyboard::Numpad1] = "Numpad 1";
	keysString[sf::Keyboard::Numpad2] = "Numpad 2";
	keysString[sf::Keyboard::Numpad3] = "Numpad 3";
	keysString[sf::Keyboard::Numpad4] = "Numpad 4";
	keysString[sf::Keyboard::Numpad5] = "Numpad 5";
	keysString[sf::Keyboard::Numpad6] = "Numpad 6";
	keysString[sf::Keyboard::Numpad7] = "Numpad 7";
	keysString[sf::Keyboard::Numpad8] = "Numpad 8";
	keysString[sf::Keyboard::Numpad9] = "Numpad 9";
	
	keysString[sf::Keyboard::F1] = "F1";
	keysString[sf::Keyboard::F2] = "F2";
	keysString[sf::Keyboard::F3] = "F3";
	keysString[sf::Keyboard::F4] = "F4";
	keysString[sf::Keyboard::F5] = "F5";
	keysString[sf::Keyboard::F6] = "F6";
	keysString[sf::Keyboard::F7] = "F7";
	keysString[sf::Keyboard::F8] = "F8";
	keysString[sf::Keyboard::F9] = "F9";
	keysString[sf::Keyboard::F10] = "F10";
	keysString[sf::Keyboard::F11] = "F11";
	keysString[sf::Keyboard::F12] = "F12";
	keysString[sf::Keyboard::F13] = "F13";
	keysString[sf::Keyboard::F14] = "F14";
	keysString[sf::Keyboard::F15] = "F15";
	
	keysString[sf::Keyboard::Pause] = "Pause";
}

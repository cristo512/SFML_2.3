#include <iostream>
#include "Game.h"


int main()
{
    Game game;

	if(!game.Init())
		return -1;

    return game.Run();
}

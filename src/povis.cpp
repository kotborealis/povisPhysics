//============================================================================
// Name        : povis.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Logger.h"
#include "Graphics.h"
#include "Game.h"
#include "GameState.h"
#include "GameStateTest.h"

using namespace PovisEngine;

int main( int argc, char* args[] )
{
	Game* game = new Game("Awoooooo");
	GameStateTest* _ = new GameStateTest(game);
	game->pushState(_);
	game->run();
	delete game;
    return 0;
}

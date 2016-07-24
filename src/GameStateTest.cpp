/*
 * GameStateTest.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "Game.h"

namespace PovisEngine {

GameStateTest::GameStateTest(Game* _game):GameState(_game){
	Logger::info("GameStateTest");
	missingTexture = game->g()->loadTexture("assets/missing.png");
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
	game->g()->removeTexture(missingTexture);
}

void GameStateTest::handleEvent(SDL_Event* event){

}
void GameStateTest::update(){

}
void GameStateTest::draw(){
	game->g()->drawTexture(missingTexture,NULL,&pos);
}

} /* namespace PovisEngine */

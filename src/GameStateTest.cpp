/*
 * GameStateTest.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "Game.h"

#include <iostream>

namespace PovisEngine {

GameStateTest::GameStateTest(Game* _game):GameState(_game){
	Logger::info("GameStateTest");
	missingTexture = game->g()->loadTexture("assets/awo.png");
	b = new PBody(100,100,100,100);
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
	game->g()->removeTexture(missingTexture);
}

void GameStateTest::handleEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEMOTION){
		int x,y;
		SDL_GetMouseState(&x,&y);
		b->setPos(v2(x,y));
		return;
	}
	if(event->type == SDL_MOUSEWHEEL){
		b->rotate(event->wheel.y*15);
	}
}
void GameStateTest::update(){

}
void GameStateTest::draw(){
	SDL_Rect rect = {
			b->bbox[0].x,
			b->bbox[0].y,
			b->width,
			b->height
	};
	SDL_Point center = {0,0};

	game->g()->drawTexture(missingTexture,NULL,&rect,b->rotation,&center);
}

} /* namespace PovisEngine */

/*
 * GameStateTest.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "Game.h"
#include "EntityPhysicTest.h"

#include <iostream>

namespace PovisEngine {

GameStateTest::GameStateTest(){
	Logger::info("GameStateTest");
	o = new EntityPhysicTest(100.f,100.f,100.f,100.f);
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEMOTION){
		int x,y;
		SDL_GetMouseState(&x,&y);
		return;
	}
	if(event->type == SDL_MOUSEWHEEL){
	}
}
void GameStateTest::update(){
	o->body->shape->angle++;
	o->body->tx.angle++;
}
void GameStateTest::draw(){
	SDL_Rect rect = {
			o->body->tx.position.x,
			o->body->tx.position.y,
			o->width,
			o->height
	};
	SDL_Point center = {rect.w/2,rect.h/2};

	Game::i().g()->drawTexture(-1,NULL,&rect,o->body->tx.angle,&center);
	o->draw();
}

} /* namespace PovisEngine */

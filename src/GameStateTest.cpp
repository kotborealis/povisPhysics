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

GameStateTest::GameStateTest(Game* _game):GameState(_game){
	Logger::info("GameStateTest");
	ents.push_back(new EntityPhysicTest(100,100,100,100));
	ents.push_back(new EntityPhysicTest(200,200,50,50));
	ents.push_back(new EntityPhysicTest(300,300,80,50));
	ents.push_back(new EntityPhysicTest(400,400,10,10));
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEMOTION){
		int x,y;
		SDL_GetMouseState(&x,&y);
		static_cast<EntityPhysicTest*>(ents[0])->body->setPos(v2(x,y));
		return;
	}
	if(event->type == SDL_MOUSEWHEEL){
		static_cast<EntityPhysicTest*>(ents[0])->body->rotate(event->wheel.y*15);
	}
}
void GameStateTest::update(){

}
void GameStateTest::draw(){
	for(auto it = ents.begin(); it != ents.end(); it++)
		(*it)->draw(game->g());
}

} /* namespace PovisEngine */

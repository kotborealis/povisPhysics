/*
 * GameStateTest.cpp
 *
 *  Created on: 24 шўы. 2016 у.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "Game.h"
#include "EntityPhysicTest.h"
#include <cstdlib>
#include <ctime>

#include <iostream>

namespace PovisEngine {

GameStateTest::GameStateTest(){
	Logger::info("GameStateTest");
	entities.push_back(new EntityPhysicTest(&physic,100.f,500.f,500.f,100.f, true));
	srand(time(NULL));
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEBUTTONDOWN){
		SDL_GetMouseState(&mouseX,&mouseY);
		float w = rand()%50+30;
		entities.push_back(new EntityPhysicTest(&physic,mouseX,mouseY,w,w, false));
		Logger::info(entities.size());
		return;
	}
	if(event->type == SDL_MOUSEWHEEL){
		EntityPhysicTest* o = static_cast<EntityPhysicTest*>(*entities.begin());
		o->body->rotate(event->wheel.y);
	}
}
void GameStateTest::update(){
	physic.update(0.2f);
}
void GameStateTest::draw(){
	for(auto it = entities.begin(); it != entities.end(); it++)
		(*it)->draw();
}

} /* namespace PovisEngine */

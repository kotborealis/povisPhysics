/*
 * GameStateTest.cpp
 *
 *  Created on: 24 шўы. 2016 у.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "Game.h"
#include "EntityPhysicTest.h"

#include <iostream>

namespace PovisEngine {

GameStateTest::GameStateTest(){
	Logger::info("GameStateTest");
	entities.push_back(new EntityPhysicTest(&physic,100.f,300.f,500.f,100.f, true));
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEBUTTONDOWN){
		SDL_GetMouseState(&mouseX,&mouseY);
		entities.push_back(new EntityPhysicTest(&physic,mouseX,mouseY,50.f,50.f, false));
		Logger::info(entities.size());
		return;
	}
	if(event->type == SDL_MOUSEWHEEL){
		EntityPhysicTest* o = static_cast<EntityPhysicTest*>(*entities.begin());
		o->body->tx.angle += event->wheel.y;
		o->body->shape->rotate(event->wheel.y);
	}
}
void GameStateTest::update(){
	physic.update(0.02f);
}
void GameStateTest::draw(){
	for(auto it = entities.begin(); it != entities.end(); it++)
		(*it)->draw();
}

} /* namespace PovisEngine */

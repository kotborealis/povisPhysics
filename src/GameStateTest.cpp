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
	entities.push_back(new EntityPhysicTest(&physic,100.f,100.f,100.f,100.f, false));
	entities.push_back(new EntityPhysicTest(&physic,100.f,500.f,100.f,100.f, true));
	entities.push_back(new EntityPhysicTest(&physic,220.f,500.f,100.f,100.f, true));
	entities.push_back(new EntityPhysicTest(&physic,340.f,500.f,100.f,100.f, true));
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEMOTION){
		int x = event->motion.x;
		int y = event->motion.y;

		EntityPhysicTest* o = static_cast<EntityPhysicTest*>(*entities.begin());
		o->body->tx.position = v2(x,y);
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

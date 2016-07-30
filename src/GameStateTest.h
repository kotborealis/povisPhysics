/*
 * GameStateTest.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GAMESTATETEST_H_
#define GAMESTATETEST_H_

#include <list>

#include "GameState.h"
#include "Logger.h"
#include "EntityPhysicTest.h"
#include "Entity.h"
#include "Physics.h"

namespace PovisEngine {

class GameStateTest: public GameState {
public:
	GameStateTest();
	~GameStateTest();

	void handleEvent(SDL_Event* event);
	void update();
	void draw();

private:
	std::list<Entity*> entities;
	Physics physic;
	int mouseX, mouseY;
};

} /* namespace PovisEngine */

#endif /* GAMESTATETEST_H_ */

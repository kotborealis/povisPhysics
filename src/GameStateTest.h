/*
 * GameStateTest.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GAMESTATETEST_H_
#define GAMESTATETEST_H_

#include <vector>

#include "GameState.h"
#include "Logger.h"
#include "EntityPhysicTest.h"
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
	EntityPhysicTest* o;
	Physics physic;
};

} /* namespace PovisEngine */

#endif /* GAMESTATETEST_H_ */

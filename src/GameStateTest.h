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
#include "Entity.h"

namespace PovisEngine {

class GameStateTest: public GameState {
public:
	GameStateTest(Game* _game);
	~GameStateTest();

	void handleEvent(SDL_Event* event);
	void update();
	void draw();

private:
	std::vector<Entity*> ents;
};

} /* namespace PovisEngine */

#endif /* GAMESTATETEST_H_ */

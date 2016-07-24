/*
 * GameStateTest.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GAMESTATETEST_H_
#define GAMESTATETEST_H_

#include "GameState.h"
#include "Logger.h"

namespace PovisEngine {

class GameStateTest: public GameState {
public:
	GameStateTest(Game* _game);
	~GameStateTest();

	void handleEvent(SDL_Event* event);
	void update();
	void draw();

private:
	short missingTexture;
	SDL_Rect pos = {0,0,100,100};
};

} /* namespace PovisEngine */

#endif /* GAMESTATETEST_H_ */

/*
 * Game.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "Graphics.h"
#include "GameState.h"
#include "Logger.h"

namespace PovisEngine {

class GameState;
class Game {
public:
	Game(std::string);
	virtual ~Game();

	void run();

	void setState(GameState* newState);
	void pushState(GameState* newState);
	void popState();


	Graphics* g(){return _g;}

private:
	inline void CState(){
		cState = states.back();
	}
	std::vector<GameState*> states;
	GameState* cState;
	Graphics* _g;
};

} /* namespace PovisEngine */

#endif /* GAME_H_ */

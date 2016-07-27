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
#include <ctime>

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
	inline void CState(){cState = states.back();}
	std::vector<GameState*> states;
	GameState* cState;
	Graphics* _g;

	void update(float);

	constexpr static float max_framerate = 60.f;
	constexpr static float min_frametime = 1000 / max_framerate;

	float time_buffer = 0.f;

	void update_needed(const float);
};

} /* namespace PovisEngine */

#endif /* GAME_H_ */

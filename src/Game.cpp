/*
 * Game.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Game.h"
#include <string>

namespace PovisEngine {

Game::Game(std::string title) {
	Logger::info("Initializing engine");
	_g = new Graphics(title, 800, 600);
}

Game::~Game() {
	Logger::info("Destroying engine");
	for(auto it = states.begin(); it != states.end(); it++)
		delete *it;
	delete _g;
}

void Game::run(){
	bool running = true;
	float delta = 1.f;
	SDL_Event event;

	Logger::info("Engine running");
	while(running){
		while(SDL_PollEvent(&event)){
			running = event.type != SDL_QUIT;
			cState->handleEvent(&event);
		}
		clock_t frame_start = std::clock();
		update(delta);
		clock_t frame_end = std::clock();
		delta = float((frame_end - frame_start) / CLOCKS_PER_SEC);
		if(delta<1000/60.f)
			SDL_Delay(1000/60.f - delta);
	}
	Logger::info("Engine stop");
}

void Game::update(float delta){
	cState->update();
	g()->clear();
	cState->draw();
	g()->render();
}

void Game::setState(GameState* newState){
	popState();
	states.push_back(newState);
	CState();
}
void Game::pushState(GameState* newState){
	states.push_back(newState);
	CState();
}
void Game::popState(){
	if(!states.empty()){
		delete states.back();
		states.pop_back();
	}
	CState();
}

} /* namespace PovisEngine */

/*
 * Game.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Game.h"

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
	SDL_Event event;

	Logger::info("Engine running");
	while(running){
		while(SDL_PollEvent(&event)){
			running = event.type != SDL_QUIT;
			cState->handleEvent(&event);
		}
		cState->update();

		g()->clear();
		cState->draw();
		g()->render();
	}
	Logger::info("Engine stop");
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

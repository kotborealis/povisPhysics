/*
 * Graphics.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Graphics.h"

namespace PovisEngine {

Graphics::Graphics(std::string title, unsigned int width, unsigned int height) {
	Logger::info("Initializing graphics");
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		Logger::error(SDL_GetError());
	}
	else{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if(window == nullptr){
			Logger::error(SDL_GetError());
		}
		else{
			renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(renderer==nullptr){
				Logger::error(SDL_GetError());
			}
			else {
				SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);
				if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
					Logger::error(SDL_GetError());
				}
			}
		}
	}
}

Graphics::~Graphics() {
	Logger::info("Destroying graphics");
	for(auto it = tMap.begin(); it!=tMap.end(); it++){
		SDL_DestroyTexture(it->second->texture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

short Graphics::loadTexture(std::string filename){
	Logger::info(std::string("Loading texture ")+filename);
	Texture* t = new Texture();
	auto loadedSurface = IMG_Load(filename.c_str());

	if(loadedSurface==nullptr){
		Logger::warn(IMG_GetError());
		return -1;
	}

	t->filename = filename;
	t->texture = SDL_CreateTextureFromSurface(renderer,loadedSurface);

	SDL_FreeSurface(loadedSurface);

	if(t->texture==nullptr){
		Logger::warn(IMG_GetError());
		return -1;
	}

	short tId = tIdCounter++;
	tMap.insert(std::pair<short,Texture*>(tId,t));

	return tId;
}

void Graphics::removeTexture(short tId){
	auto t = tMap.at(tId);
	Logger::info(std::string("Destroying texture ")+t->filename);
	SDL_DestroyTexture(t->texture);
	tMap.erase(tId);
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

void Graphics::render() {
    SDL_RenderPresent(renderer);
}

void Graphics::drawTexture(short tId, SDL_Rect* srcrect, SDL_Rect* dstrect){
	SDL_RenderCopy(renderer, tMap.at(tId)->texture, srcrect, dstrect);
}

} /* namespace PovisEngine */

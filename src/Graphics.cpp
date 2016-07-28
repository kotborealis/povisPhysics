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
				if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
					Logger::error(SDL_GetError());
				}
				if(TTF_Init() == -1){
					Logger::error(SDL_GetError());
				}
			}
		}
	}
	fontDebug = TTF_OpenFont("assets/fonts/Monospace.ttf",16);
	loadTexture("assets/textures/missing.png");
}

Graphics::~Graphics() {
	Logger::info("Destroying graphics");
	for(auto it = tMap.begin(); it!=tMap.end(); it++){
		SDL_DestroyTexture(it->second->texture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
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
	fMap.insert(std::pair<std::string,short>(filename,tId));

	return tId;
}

void Graphics::removeTexture(short tId){
	auto t = tMap.at(tId);
	Logger::info(std::string("Destroying texture ")+t->filename);
	SDL_DestroyTexture(t->texture);
	tMap.erase(tId);
}

void Graphics::clear() {
	SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(renderer);
}

void Graphics::render() {
    SDL_RenderPresent(renderer);
}

void Graphics::drawTexture(short tId, SDL_Rect* srcrect, SDL_Rect* dstrect){
	drawTexture(tId, srcrect, dstrect, 0, NULL);
}
void Graphics::drawTexture(short tId, SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, SDL_Point* center){
	Texture* t = tMap.at(tId);
	if(t==NULL)
		t = tMap.at(-1);

	SDL_RenderCopyEx(renderer, t->texture, srcrect, dstrect, angle, center, SDL_FLIP_NONE);
}

void Graphics::drawRect(SDL_Rect* rect, int r, int g, int b, int a){
	SDL_SetRenderDrawColor(renderer, r,g,b,a);
	SDL_RenderDrawRect(renderer, rect);
}

void Graphics::drawText(SDL_Rect* pos, std::string text, int r, int g, int b, int a){
	SDL_Color color = {r,g,b,a};
	SDL_Surface* surface = TTF_RenderText_Blended(fontDebug, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect rect = {pos->x, pos->y, surface->w, surface->h};
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

} /* namespace PovisEngine */

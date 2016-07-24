/*
 * Graphics.h
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Logger.h"

namespace PovisEngine {

struct Texture {
	std::string filename;
	SDL_Texture* texture;
	short tId;
};

class Graphics {
public:
	Graphics(std::string title, unsigned int width, unsigned int height);
	virtual ~Graphics();

	short loadTexture(std::string filename);
	void removeTexture(short tId);

	void clear();
	void render();

	void drawTexture(short tId, SDL_Rect* srcrect, SDL_Rect* dstrect);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	short tIdCounter = 0;
	std::map<short,Texture*> tMap;
};

} /* namespace PovisEngine */

#endif /* GRAPHICS_H_ */

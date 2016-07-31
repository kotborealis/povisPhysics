/*
 * Graphics.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

	short lookUpTextureByFilename(std::string filename);

	void clear();
	void render();

	void drawTexture(short tId, SDL_Rect* srcrect, SDL_Rect* dstrect);
	void drawTexture(short tId, SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, SDL_Point* center);

	void drawRect(SDL_Rect* rect, int r, int g, int b, int a);
	void drawRect(int x, int y, int w, int h, int r, int g, int b, int a);

	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);

	void drawText(SDL_Rect* pos, std::string text, int r, int g, int b, int a);
	void drawText(int x, int y, std::string text, int r, int g, int b, int a);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	short tIdCounter = -1;
	std::map<short,Texture*> tMap;
	std::map<std::string,short> fMap;

	TTF_Font* fontDebug;
};

} /* namespace PovisEngine */

#endif /* GRAPHICS_H_ */

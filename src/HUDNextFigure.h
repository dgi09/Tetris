#pragma once 
#include "Figure.h"
#include "sdl.h"


class HUDNextFigure
{
	int x,y;
	int blockSize;

	Figure figure;
	SDL_Rect frameRect;
	SDL_Rect blockRect;
public:
	HUDNextFigure();

	void SetPosition(int x,int y);
	void SetBlockSize(int size);

	void SetFigure(Figure f);
	void Draw(SDL_Renderer * renderer);
};

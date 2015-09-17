#pragma once 

#include "IObserver.h"
#include "SDL.h"
#include "SDL_ttf.h"


class Arena;

class HUDPoints : public IObserver
{
	bool ptNeedRedraw;
	bool btNeedRedraw;
	int points;
	int best;

	SDL_Texture * ptTexture;
	SDL_Texture * btTexture;

	TTF_Font * font;
	Arena * arena;

	int x,y;
	SDL_Rect ptFrame;
	SDL_Rect btFrame;

public:
	HUDPoints();
	~HUDPoints();

	void SetArena(Arena * a);
	void Notify(int type);
	void Draw(SDL_Renderer * renderer);
	void SetPosition(int x,int y);

private:
	void RecreatePointsTexture(SDL_Renderer * renderer);
	void RecreateBestTexture(SDL_Renderer * renderer);
};
#include "HUDPoints.h"
#include "ArenaEventTypes.h"
#include "Arena.h"
#include <string>

HUDPoints::HUDPoints()
{
	font = TTF_OpenFont("fonts/arial.ttf",21);
	ptTexture = nullptr;
	btTexture = nullptr;

	best = 0;

	btNeedRedraw = true;
}

HUDPoints::~HUDPoints()
{
	if(font != nullptr)
		TTF_CloseFont(font);

	if(ptTexture != nullptr)
		SDL_DestroyTexture(ptTexture);

	if(btTexture != nullptr)
		SDL_DestroyTexture(btTexture);

}

void HUDPoints::Notify(int type)
{
	if(type == PointsChanged)
	{
		ptNeedRedraw = true;
		points = arena->GetPoints();
	}

	if(type == GameEnd)
	{
		if(best < arena->GetPoints())
		{
			best = arena->GetPoints();
			btNeedRedraw = true;
		}
	}
	
}

void HUDPoints::Draw(SDL_Renderer * renderer)
{
	if(ptNeedRedraw)
	{
		RecreatePointsTexture(renderer);
		ptNeedRedraw = false;
	}

	if(btNeedRedraw)
	{
		RecreateBestTexture(renderer);
		btNeedRedraw = false;
	}

	SDL_RenderCopy(renderer,ptTexture,nullptr,&ptFrame);
	SDL_RenderCopy(renderer,btTexture,nullptr,&btFrame);


}

void HUDPoints::RecreatePointsTexture(SDL_Renderer * renderer)
{
	if(ptTexture != nullptr)
		SDL_DestroyTexture(ptTexture);

	std::string text = "Points : " + std::to_string(points);

	SDL_Color c;
	c.r = 255;
	c.g = 255;
	c.b = 255;
	c.a = 255;

	SDL_Surface * s = TTF_RenderText_Solid(font,text.c_str(),c);
	ptFrame.w = s->w;
	ptFrame.h = s->h;

	ptTexture = SDL_CreateTextureFromSurface(renderer,s);

	SDL_FreeSurface(s);

}

void HUDPoints::SetArena(Arena * a)
{
	arena = a;
}

void HUDPoints::SetPosition(int x,int y)
{
	this->x = x;
	this->y =y ;
	ptFrame.x = x;
	ptFrame.y = y;
}

void HUDPoints::RecreateBestTexture(SDL_Renderer * renderer)
{
	if(btTexture != nullptr)
		SDL_DestroyTexture(btTexture);

	std::string text = "Best : " + std::to_string(best);

	SDL_Color c;
	c.r = 255;
	c.g = 255;
	c.b = 255;
	c.a = 255;

	SDL_Surface * s = TTF_RenderText_Solid(font,text.c_str(),c);
	btFrame.w = s->w;
	btFrame.h = s->h;

	btFrame.x = x;
	btFrame.y = y + ptFrame.h + 5;

	btTexture = SDL_CreateTextureFromSurface(renderer,s);

	SDL_FreeSurface(s);

	
}

#include "HUDNextFigure.h"

HUDNextFigure::HUDNextFigure()
{

}

void HUDNextFigure::SetPosition(int x,int y)
{
	frameRect.x = x;
	frameRect.y = y;
	this->x = x;
	this->y = y;
}

void HUDNextFigure::SetBlockSize(int size)
{
	blockRect.w = blockRect.h = size;
	blockSize = size;

	frameRect.w = frameRect.h =  blockSize * 3 + 1; 

}

void HUDNextFigure::SetFigure(Figure f)
{
	figure = f;
}

void HUDNextFigure::Draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer,0,0,255,255);
	SDL_RenderDrawRect(renderer,&frameRect);

	for(int i = 0;i < 3;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			Block b = figure.GetBlock(i,j);
			if(b.filled)
			{
				blockRect.x = x + blockSize * i + 1;
				blockRect.y = y + blockSize * j + 1;

				SDL_SetRenderDrawColor(renderer,b.color.r,b.color.g,b.color.b,255);
				SDL_RenderFillRect(renderer,&blockRect);

				SDL_SetRenderDrawColor(renderer,0,0,0,255);
				SDL_RenderDrawRect(renderer,&blockRect);
			}
		}
	}
}

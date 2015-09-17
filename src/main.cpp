#include <windows.h>
#include "SDL.h"
#include "SDL_ttf.h"

#include "Arena.h"
#include "FigureGenerator.h"
#include "Figure.h"
#include <chrono>
#include <random>
#include "FigureManager.h"
#include "HUDNextFigure.h"
#include "HUDPoints.h"


int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	srand(time(0));

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_Window * window = SDL_CreateWindow("Tetris",200,50,400,610,SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


	
	SDL_Event e;

	Arena a(10,27);
	a.SetPosition(5,5);
	a.SetBlockSize(22,22);
	

	HUDNextFigure hud;
	hud.SetPosition(240,220);
	hud.SetBlockSize(40);

	HUDPoints hudPoints;
	hudPoints.SetArena(&a);
	hudPoints.SetPosition(240,150);
	
	a.AddObserver(&hudPoints);
	
	FigureManager mgr;
	mgr.ConnectToArena(&a);
	mgr.SetHUD(&hud);
	mgr.PlaceFirst();

	a.SetPoints(0);

	SDL_Texture * title;
	TTF_Font * font = TTF_OpenFont("fonts/iomanoid.ttf",60);
	SDL_Color textColor;
	textColor.r = textColor.g = textColor.b = textColor.a = 150;
	SDL_Surface * surface = TTF_RenderText_Solid(font,"TetriS",textColor);

	SDL_Rect textRect;
	textRect.x = 240;
	textRect.y = 50;
	textRect.w = surface->w;
	textRect.h = surface->h;

	title = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);

	
	bool run = true;
	while(run)
	{

		auto begin = std::chrono::high_resolution_clock::now();

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				run = false;
				break;
			}

			if(e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_LEFT)
				{
					
					a.MoveActiveFigureLeft();
				}

				if(e.key.keysym.sym == SDLK_RIGHT)
				{
					
					a.MoveActiveFigureRight();
				}

				if(e.key.keysym.sym == SDLK_SPACE)
				{
					a.AttempRotation();
				}

				if(e.key.keysym.sym == SDLK_DOWN)
				{
					a.SpeedUpFalling();
				}
			}

			if(e.type == SDL_KEYUP)
			{
				
				if(e.key.keysym.sym == SDLK_DOWN)
				{
					a.StopSpeedUpFalling();
				}
			}
		
		}


		a.Update();
		
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer,title,nullptr,&textRect);
		hudPoints.Draw(renderer);
		a.Draw(renderer);
		hud.Draw(renderer);


		SDL_RenderPresent(renderer);

		auto end = std::chrono::high_resolution_clock::now();

		long ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

		if(ms < 40)
			SDL_Delay(40 - ms);

	}

	TTF_CloseFont(font);
	return 0;
}
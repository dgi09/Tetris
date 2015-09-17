#pragma once 
#include "Figure.h"
#include "Block.h"
#include "Observee.h"

#include "SDL.h"
#include <chrono>

enum UpdateMode
{
	FigureUpdate,
	RowDestruction
};

class Arena : public Observee
{
	int x,y;
	int width;
	int height;
	int blockWidth;
	int blockHeight;

	Block * blocks;

	Figure activeFigure;
	bool hasActive;

	SDL_Rect drawRect;
	SDL_Rect frameRect;

	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	long wantedDuration;
	long originalDuration;
	UpdateMode upMode;

	int points;
	int currentProgressionPoints;
	int startPrograssionPoints;
	int pointsBonus;
public:

	Arena(int w,int h);
	~Arena();

	void SetPosition(int x,int y);
	void SetBlockSize(int w,int h);

	void Draw(SDL_Renderer * renderer);
	void Update();

	void SetActiveFigure(Figure f);
	void Clear();

	void MoveActiveFigureLeft();
	void MoveActiveFigureRight();

	int GetWidht();
	int GetHeight();

	void AttempRotation();
	void SpeedUpFalling();
	void StopSpeedUpFalling();

	int GetPoints();
	void SetPoints(int p);

private:
	void DrawBlock(SDL_Renderer * renderer,Block & b,int locX,int locY);
	void PlaceActiveFigure();

	bool IsPlacementAllowed(Figure & f);

	void UpdateFigure();
	void UpdateRowDestruction();
	void OnRowRestroy();
	void Reset();
	
	void Progress();
};

#pragma once 
#include "IObserver.h"
#include "Figure.h"

class HUDNextFigure;
class Arena;

class FigureManager : public IObserver
{
	Arena * arena;
	HUDNextFigure * hud;

	Figure next;
public:

	void ConnectToArena(Arena * a);
	void SetHUD(HUDNextFigure * h);

	void Notify(int type);
	
	
	void PlaceFirst();

private:
	Figure GenerateRandomFigure();
	void PlaceFigure();
};
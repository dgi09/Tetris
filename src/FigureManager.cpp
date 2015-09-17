#include "FigureManager.h"
#include "Arena.h"
#include "ArenaEventTypes.h"
#include <random>
#include "FigureGenerator.h"
#include "HUDNextFigure.h"


void FigureManager::ConnectToArena(Arena * a)
{
	arena = a;
	arena->AddObserver(this);
}

void FigureManager::Notify(int type)
{
	if(type == (int)FigurePlaced)
	{
		 PlaceFigure();
	}
}

Figure FigureManager::GenerateRandomFigure()
{
	int r = rand() % 7 + 1;

	switch (r)
	{
	case 1:
		return FigureGenerator::CreateCube();
	case 2:
		return FigureGenerator::CreateStick();
	case 3:
		return FigureGenerator::CreateInvertedL();
	case 4:
		return FigureGenerator::CreateInvertedZ();
	case 5:
		return FigureGenerator::CreateL();
	case 6:
		return FigureGenerator::CreateZ();
	case 7:
		return FigureGenerator::CreateT();
	default:
		return FigureGenerator::CreateL();
		break;
	}

	
}


void FigureManager::PlaceFigure()
{
	Figure f = GenerateRandomFigure();

	f.SetPosition(arena->GetWidht()/2 - 1,0);


	arena->SetActiveFigure(next);
	hud->SetFigure(f);
	next = f;
}

void FigureManager::SetHUD(HUDNextFigure * h)
{
	hud = h;
}

void FigureManager::PlaceFirst()
{
	Figure f = GenerateRandomFigure();
	f.SetPosition(arena->GetWidht()/2 - 1,0);

	arena->SetActiveFigure(f);

	next = GenerateRandomFigure();
	next.SetPosition(arena->GetWidht()/2 - 1,0);

	hud->SetFigure(next);
}

#include "Arena.h"
#include "ArenaEventTypes.h"


#include <chrono>
#include <algorithm>

Arena::Arena(int w,int h)
{
	hasActive = false;

	width = w;
	height = h;

	blocks = new Block[w * h];

	Reset();
	
}

Arena::~Arena()
{
	delete[] blocks;
}


void Arena::SetPosition(int x,int y)
{
	this->x = x;
	this->y = y;

	frameRect.x = x;
	frameRect.y = y;
}

void Arena::SetBlockSize(int w,int h)
{
	drawRect.w = w;
	drawRect.h = h;

	blockWidth = w;
	blockHeight = h;

	frameRect.w = width * blockWidth + 2;
	frameRect.h = height * blockHeight + 2;


}

void Arena::Draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer,0,255,0,255);
	SDL_RenderDrawRect(renderer,&frameRect);

	if(hasActive)
		for(int i = 0;i < 3;i++)
		{
			for(int j = 0;j < 3;j++)
			{
				Block & b = activeFigure.GetBlock(i,j);
				if(b.filled)
				{
					DrawBlock(renderer,b,activeFigure.GetX() + i,activeFigure.GetY() + j);
				}
			}
		}

		for(int i = 0;i < width;i++)
		{
			for(int j = 0;j < height;j++)
			{
				Block & b = blocks[j * width + i];
				if(b.filled)
					DrawBlock(renderer,b,i,j);
			}
		}

}

void Arena::Update()
{
	if(upMode == FigureUpdate)
		UpdateFigure();
	else UpdateRowDestruction();
}

void Arena::SetActiveFigure(Figure f)
{
	if(!IsPlacementAllowed(f))
		Reset();

	
	hasActive = true;
	activeFigure = f;
	wantedDuration = originalDuration;
}

void Arena::Clear()
{
	for(int i = 0;i < width;i++)
	{
		for(int j = 0;j < height;j++)
		{
			Block & b = blocks[j * width + i];
			b.filled = false;
			b.color.r = 255;
			b.color.g = b.color.b = 0;
			b.color.a = 255;
		}
	}
}

void Arena::DrawBlock(SDL_Renderer * renderer,Block & b,int locX,int locY)
{
	drawRect.x = x + locX * blockWidth + 1;
	drawRect.y = y + locY * blockHeight + 1;

	SDL_SetRenderDrawColor(renderer,b.color.r,b.color.g,b.color.b,255);
	SDL_RenderFillRect(renderer,&drawRect);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderDrawRect(renderer,&drawRect);
}

void Arena::PlaceActiveFigure()
{
	int xMax,yMax;
	if(activeFigure.GetX() + 3 >= width)
	{
		xMax = width;
	}else xMax = activeFigure.GetX() + 3;

	if(activeFigure.GetY() + 3 >= height)
	{
		yMax = height;
	}else yMax = activeFigure.GetY() + 3;

	for(int i = activeFigure.GetX(),locX = 0;i < xMax;i++,locX++)
	{
		for(int j = activeFigure.GetY(),locY = 0;j < yMax;j++,locY++)
		{
			Block & b = activeFigure.GetBlock(locX,locY);
			if(b.filled)
				blocks[j * width + i] = b;
		}
	}

	hasActive = false;

}

void Arena::MoveActiveFigureLeft()
{
	if(hasActive == false)
		return;

	int maxMoveLeft = 100;

	for(int i = 0;i < 3;i++)
	{
		int leftestPoint = activeFigure.GetLeftestByRow(i);
		int currentMaxMove;

		if(leftestPoint != -1)
		{

			int h;
			int reach = activeFigure.GetX() + leftestPoint - 1;

			if(reach <= 0)
				h = 0;
			else 
				h = reach;	


			bool have = false;

			for(int j = activeFigure.GetX() + leftestPoint-1;j >= h;j--)
			{
				if(blocks[((activeFigure.GetY() + i) * width) + j].filled)
				{
					currentMaxMove = activeFigure.GetX() + leftestPoint - 1 - j;
					have = true;
					break;
				}
			}

			if(have == false)
				currentMaxMove = std::min(1,activeFigure.GetX() + leftestPoint);

			if(currentMaxMove < maxMoveLeft)
				maxMoveLeft = currentMaxMove;
		}
	}

	activeFigure.SetPosition(activeFigure.GetX() - maxMoveLeft,activeFigure.GetY());
}

void Arena::MoveActiveFigureRight()
{
	if(hasActive == false)
		return;

	int maxMoveRight = 100;

	for(int i = 0;i < 3;i++)
	{
		int rightestPoint = activeFigure.GetRightestByRow(i);
		int currentMaxMove;

		if(rightestPoint != -1)
		{

			int h;
			int reach = activeFigure.GetX() + rightestPoint + 2;
			if( reach >= width)
				h = width;
			else 
				h = reach;	


			bool have = false;
			for(int j = activeFigure.GetX() + rightestPoint +1;j < h;j++)
			{
				if(blocks[((activeFigure.GetY() + i) * width) + j].filled)
				{
					currentMaxMove = j - (activeFigure.GetX() + rightestPoint + 1);
					have = true;
					break;
				}
			}

			if(!have)
				currentMaxMove = std::min((h - (activeFigure.GetX() + rightestPoint + 1)),1);


			if(currentMaxMove < maxMoveRight)
				maxMoveRight = currentMaxMove;
		}
	}

	activeFigure.SetPosition(activeFigure.GetX() + maxMoveRight,activeFigure.GetY());
}

int Arena::GetWidht()
{
	return width;
}

int Arena::GetHeight()
{
	return height;
}

void Arena::AttempRotation()
{
	if(hasActive)
	{
		if(activeFigure.IsRotateable())
		{
			
			Figure f = activeFigure.Rotate();
			if(IsPlacementAllowed(f))
				activeFigure = f;
		}
		
	}
}

bool Arena::IsPlacementAllowed(Figure & f)
{
	for(int i = 0 ;i < 3;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			if(f.GetBlock(i,j).filled)
			{
				if(f.GetX() + i < 0 || f.GetX() + i >= width || f.GetY() + j < 0 || f.GetY() + j >= height)
					return false;

				if(blocks[(f.GetY() + j) * width + f.GetX() + i].filled)
					return false;
			}
		}
	}

	return true;
}

void Arena::UpdateFigure()
{
	auto now = std::chrono::high_resolution_clock::now();

	long long currDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

	if(currDuration < wantedDuration)
		return;
	else 
		start = now;


	if(hasActive)
	{
		int maxMoveDown = 100;
		bool collision = false;

		for(int i = 0;i < 3;i++)
		{
			int lowestPoint = activeFigure.GetLowestByColumn(i);
			int currentMaxMove;

			if(lowestPoint != -1)
			{
				int h;
				int reach = activeFigure.GetY() + lowestPoint + 2;

				if( reach >= height)
					h = height;
				else 
					h = reach;	

				bool have = false;
				for(int j = activeFigure.GetY() + lowestPoint + 1;j < h;j++)
				{
					if(blocks[(j * width) + activeFigure.GetX() + i].filled)
					{
						currentMaxMove = j - activeFigure.GetY() - lowestPoint - 1;
						collision = true;
						have = true;
						break;
					}
				}

				if(!have)
				{
					currentMaxMove = h - (activeFigure.GetY() + lowestPoint + 1);

					if(h == height)
						collision = true;
				}

				if(currentMaxMove < maxMoveDown)
					maxMoveDown = currentMaxMove;
			}

		}

		activeFigure.SetPosition(activeFigure.GetX(),activeFigure.GetY() + maxMoveDown);
		if(collision)
		{
			PlaceActiveFigure();
			upMode = RowDestruction;
		}
	}
}

void Arena::UpdateRowDestruction()
{
	auto now = std::chrono::high_resolution_clock::now();

	long long  currDuration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

	if(currDuration < 500)
		return;
	else 
		start = now;

	int moveDownRow;
	bool filled = false;
	for(int i = height-1;i >= 0;i--)
	{
		bool rowFilled = true;
		for(int j = 0;j < width;j++)
		{
			if(blocks[i * width + j].filled == false)
			{
				rowFilled = false;
				break;
			}
		}

		if(rowFilled)
		{
			moveDownRow = i;
			filled = true;
			break;
		}
	}

	if(filled)
	{
		for(int i = moveDownRow;i > 0;i--)
		{
			for(int j = 0;j < width;j++)
			{
				blocks[i * width + j] = blocks[(i-1) * width + j];
			}
		}

		OnRowRestroy();
	}
	else 
	{
		NotifyObservers((int)FigurePlaced);
		upMode = FigureUpdate;
	}

}

void Arena::SpeedUpFalling()
{
	if(upMode == FigureUpdate)
	{
		double prc = 85.0/100.0;
		int rem = (int)(originalDuration * prc);
		wantedDuration = originalDuration - rem;
	}
	
}

int Arena::GetPoints()
{
	return points;
}

void Arena::SetPoints(int p)
{
	points = p;

	NotifyObservers((int)PointsChanged);
}

void Arena::OnRowRestroy()
{
	SetPoints(points + pointsBonus);

	if(GetPoints() >= currentProgressionPoints)
	{
		Progress();
	}
}

void Arena::Reset()
{
	NotifyObservers((int)GameEnd);

	Clear();
	SetPoints(0);

	start = std::chrono::high_resolution_clock::now();
	originalDuration = 300;
	wantedDuration = originalDuration;

	upMode = FigureUpdate;

	startPrograssionPoints = 40;
	pointsBonus = 30;

	currentProgressionPoints = startPrograssionPoints;
}

void Arena::Progress()
{
	currentProgressionPoints += (int)(currentProgressionPoints * 60.0 / 100.0);
	pointsBonus += (int)(pointsBonus * 15.0/100.0);

	originalDuration -= (int)(originalDuration * 8.0/100.0);
}

void Arena::StopSpeedUpFalling()
{
	wantedDuration = originalDuration;
}







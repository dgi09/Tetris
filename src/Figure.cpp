#include "Figure.h"


Figure::Figure()
{
	x = y = 0;
	
}

void Figure::Clear()
{
	for(int i = 0;i < 3;i++)
	{
		for(int j = 0;j < 3;j++)
			blocks[i][j].filled = false;
	}
}

void Figure::FillBlock(short x,short y)
{
	Block & b = blocks[x][y];
	b.filled = true;
	b.color = color;
}

Block Figure::GetBlock(short x,short y)
{
	return blocks[x][y];
}

void Figure::SetColor(SDL_Color color)
{
	this->color = color;
}


void Figure::SetPosition(short x,short y)
{
	this->x = x;
	this->y = y;
}

short Figure::GetX()
{
	return x;
}

short Figure::GetY()
{
	return y;
}

void Figure::CalcPorps()
{
	lowestY = 0;

	for(int i = 0;i < 3;i++)
	{
		lowestOnColumn[i] = -1;
		leftestOnRow[i] = -1;
		rightestOnRow[i] = -1;
	}

	for(int i = 0;i < 3;i++)
	{
		for(int j = 2;j >= 0;j--)
		{
			if(blocks[i][j].filled)
			{
				lowestOnColumn[i] = j;
				if(lowestY < j)
					lowestY = j;

				break;
			}
		}
	}

	for(int i = 0;i < 3;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			if(blocks[j][i].filled)
			{
				leftestOnRow[i] = j;
				break;
			}
		}

		for(int j = 2;j >= 0;j--)
		{
			if(blocks[j][i].filled)
			{
				rightestOnRow[i] = j;
				break;
			}
		}
	}

}

int Figure::GetLowestY()
{
	return lowestY;
}

int Figure::GetLowestByColumn(int col)
{
	return lowestOnColumn[col];
}

int Figure::GetLeftestByRow(int row)
{
	return leftestOnRow[row];
}

int Figure::GetRightestByRow(int row)
{
	return rightestOnRow[row];
}

Figure Figure::Rotate()
{
	Figure n;
	n.SetPosition(x,y);


	for(int i = 2,k = 0;i >= 0;i--,k++)
	{
		for(int j = 0;j < 3;j++)
		{
			n.blocks[k][j] = blocks[j][i];
		}
	}

	n.CalcPorps();

	return n;
}

void Figure::SetRotateable(bool val)
{
	rotateable = val;
}

bool Figure::IsRotateable()
{
	return rotateable;
}

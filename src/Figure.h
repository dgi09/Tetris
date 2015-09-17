#pragma once 
#include "Block.h"

class Figure 
{
	Block blocks[3][3];
	SDL_Color color;

	short x,y;

	int lowestOnColumn[3];
	int leftestOnRow[3];
	int rightestOnRow[3];

	int lowestY;

	bool rotateable;
public:

	Figure();
	void Clear();
	void FillBlock(short x,short y);
	Block GetBlock(short x,short y);
	void SetColor(SDL_Color color);

	void SetPosition(short x,short y);
	short GetX();
	short GetY();

	void CalcPorps();


	int GetLowestY();
	int GetLowestByColumn(int col);
	int GetLeftestByRow(int row);
	int GetRightestByRow(int row);

	Figure Rotate();

	void SetRotateable(bool val);
	bool IsRotateable();
};
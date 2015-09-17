#pragma once 
#include "Figure.h"

class FigureGenerator
{
public:
	static Figure CreateCube();
	static Figure CreateStick();
	static Figure CreateZ();
	static Figure CreateL();
	static Figure CreateInvertedZ();
	static Figure CreateInvertedL();
	static Figure CreateT();
};

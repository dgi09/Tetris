#include "FigureGenerator.h"


Figure FigureGenerator::CreateCube()
{
	Figure f;
	f.Clear();
	SDL_Color c;
	c.r = 255;
	c.g = c.b = 0;

	f.SetColor(c);
	f.SetRotateable(false);


	f.FillBlock(0,0);
	f.FillBlock(1,0);
	f.FillBlock(0,1);
	f.FillBlock(1,1);

	f.CalcPorps();
	
	return f;
}

Figure FigureGenerator::CreateStick()
{
	Figure f;
	f.Clear();

	f.SetRotateable(true);
	SDL_Color c;
	c.g = 255;
	c.r = c.b = 0;

	f.SetColor(c);


	f.FillBlock(0,1);
	f.FillBlock(1,1);
	f.FillBlock(2,1);

	f.CalcPorps();

	return f;
}

Figure FigureGenerator::CreateZ()
{
	Figure f;
	f.Clear();

	SDL_Color c;
	c.b = 255;
	c.g = 255;
	c.r = 0;
	f.SetColor(c);
	f.SetRotateable(true);

	f.FillBlock(0,0);
	f.FillBlock(0,1);
	f.FillBlock(1,1);
	f.FillBlock(1,2);

	f.CalcPorps();

	return f;
}

Figure FigureGenerator::CreateL()
{
	Figure f;
	f.Clear();

	SDL_Color c;
	c.g = 255;
	c.r = 255;
	c.b = 0;

	f.SetColor(c);
	f.SetRotateable(true);

	f.FillBlock(1,0);
	f.FillBlock(1,1);
	f.FillBlock(1,2);
	f.FillBlock(2,2);

	f.CalcPorps();

	return f;
}

Figure FigureGenerator::CreateInvertedZ()
{
	Figure f;
	f.Clear();

	SDL_Color c;
	c.b = 255;
	c.r = c.g = 0;

	f.SetColor(c);
	f.SetRotateable(true);

	f.FillBlock(0,2);
	f.FillBlock(0,1);
	f.FillBlock(1,1);
	f.FillBlock(1,0);

	f.CalcPorps();

	return f;
}

Figure FigureGenerator::CreateInvertedL()
{
	Figure f;
	f.Clear();

	SDL_Color c;
	c.g = 255;
	c.r = 255;
	c.b = 0;

	f.SetColor(c);
	f.SetRotateable(true);

	f.FillBlock(1,0);
	f.FillBlock(1,1);
	f.FillBlock(1,2);
	f.FillBlock(2,0);

	f.CalcPorps();

	return f;
}

Figure FigureGenerator::CreateT()
{
	Figure f;
	f.Clear();

	SDL_Color c;
	c.g = 100;
	c.r = 50;
	c.b = 255;

	f.SetColor(c);
	f.SetRotateable(true);

	f.FillBlock(0,2);
	f.FillBlock(1,2);
	f.FillBlock(2,2);
	f.FillBlock(1,1);

	f.CalcPorps();

	return f;
}

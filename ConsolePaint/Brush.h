#pragma once
#include "pdcurses/curses.h"
#include "Canvas.h"
#include "Vector.h"



/** Base brush
* This specfic brush just places characters in a given point*/
class Brush
{
public:
	unsigned char Character = 'a';
	uint32_t Size;

	Brush() {}

	virtual void Apply(Canvas* canvas, Vector loc)
	{
		if (canvas)
		{
			canvas->AddElement(loc, new Element(Character));
		}
	}
};


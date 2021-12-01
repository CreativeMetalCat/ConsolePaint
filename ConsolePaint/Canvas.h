#pragma once
#include <map>
#include  "Element.h"
#include "Vector.h"
#include "pdcurses/curses.h"

class Canvas
{
public:
	std::map<unsigned int , Element*> CanvasElements = std::map<unsigned int, Element*>();

	Vector Size;

	Canvas(Vector size):Size(size){}

	unsigned int ConvertToId(Vector vec)
	{
		return vec.X + vec.Y * Size.X;
	}

	void AddElement(Vector loc, Element* elem)
	{
		CanvasElements.insert({ ConvertToId(loc),elem });
	}

	/*This is a helper function with only one purpose, fix holes that appear when mouse is moved too fast*/
	void Line(Vector start, Vector end,unsigned char symbol)
	{
        //source
        //http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
        //
        const bool steep = (fabs(end.Y - start.Y) > fabs(end.X - start.X));
        if (steep)
        {
            std::swap(start.X, start.Y);
            std::swap(end.X, end.Y);
        }

        if (start.X > end.X)
        {
            std::swap(start.X, end.X);
            std::swap(start.Y, end.Y);
        }

        const float dx = end.X - start.X;
        const float dy = fabs(end.Y - start.Y);

        float error = dx / 2.0f;
        const int ystep = (start.Y < end.Y) ? 1 : -1;
        int y = (int)start.Y;

        const int maxX = (int)end.X;

        for (int x = (int)start.X; x <= maxX; x++)
        {
            if (steep)
            {
                mvaddch(y, x, symbol);
            }
            else
            {
                mvaddch(y, x, symbol);
            }

            error -= dy;
            if (error < 0)
            {
                y += ystep;
                error += dx;
            }
        }
	}
};


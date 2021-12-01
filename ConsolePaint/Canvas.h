#pragma once
#include <map>
#include  "Element.h"
#include "Vector.h"
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
};


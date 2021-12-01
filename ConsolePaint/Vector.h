#pragma once

#include <iostream>
#include <string>
/** Two dimensional vector*/
struct Vector
{
public:
	int X = 0;
	int Y = 0;

	Vector(int x, int y) :X(x), Y(y) {}

	Vector operator+(Vector& vec)
	{
		return Vector(this->X + vec.X, this->Y + vec.Y);
	}

	Vector operator+(Vector vec)
	{
		return Vector(this->X + vec.X, this->Y + vec.Y);
	}

	Vector operator-(Vector& vec)
	{
		return Vector(this->X - vec.X, this->Y - vec.Y);
	}

	Vector operator-(Vector vec)
	{
		return Vector(this->X - vec.X, this->Y - vec.Y);
	}

	friend std::ostream& operator<< (std::ostream& out, Vector vec)
	{
		out << "X: " << vec.X << " Y: " << vec.Y;
		return out;
	}

	std::string ToString()
	{
		return "X: " + std::to_string(X) + " Y: " + std::to_string(Y);
	}

	bool operator==(Vector vec)
	{
		return X == vec.X && Y == vec.Y;
	}

	bool operator<(Vector const& vec)
	{
		return  X < vec.X && Y < vec.Y;
	}

	bool operator==(Vector const& vec) const
	{
		return X == vec.X && Y == vec.Y;
	}

	bool operator()(Vector const& lhs, Vector const& rhs) const
	{
		return lhs == rhs || 
			(lhs.X < rhs.X && lhs.Y < rhs.Y);
	}
};
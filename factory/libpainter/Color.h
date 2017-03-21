#pragma once
#include <string>


enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black,
	White,
};

namespace
{
	std::string ToString(Color color)
	{
		std::string result;
		switch (color)
		{
		case Color::Black:
			return "black";
			break;
		case Color::Blue:
			return "black";
			break;
		case Color::Green:
			return "green";
			break;
		case Color::Pink:
			return "pink";
			break;
		case Color::Red:
			return "red";
			break;
		case Color::White:
			return "white";
			break;
		case Color::Yellow:
			return "yellow";
			break;
		}
		return "black";
	}
}
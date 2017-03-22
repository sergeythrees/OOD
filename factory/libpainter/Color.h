#pragma once
#include <string>
#include <map>


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
	std::map<std::string, Color> colorMap = {
		{ "green", Color::Green },
		{ "red", Color::Red },
		{ "blue", Color::Blue },
		{ "yellow", Color::Yellow },
		{ "pink", Color::Pink },
		{ "black", Color::Black },
		{ "white", Color::White }
	};

	std::string ToString(Color color)
	{
		std::string result;
		for (auto colorInMap : colorMap)
		{
			if (colorInMap.second == color)
				result = colorInMap.first;
		}
		return result;
	}
	Color StringToColor(const std::string& colorName)
	{
		std::string result = "black";
		try
		{
			return colorMap.at(colorName);
		}
		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("Unknown color name");
		}
	}
}
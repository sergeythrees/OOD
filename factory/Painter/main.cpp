// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Analog Clock", sf::Style::Close, settings);
	
	return 0;
}


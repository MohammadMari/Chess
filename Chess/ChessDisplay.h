#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class ChessDisplay
{
public:
	void DisplayBoard(int piece[][8], RenderWindow& window);
	int* SetSelected(Vector2i location);

} extern cDisp;
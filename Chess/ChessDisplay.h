#pragma once

#include <SFML/Graphics.hpp>
#include "ChessPiece.h"

using namespace sf;

class ChessDisplay
{
public:
	void DisplayBoard(ChessPiece **piece, RenderWindow& window);
	int* SetSelected(Vector2i location);

} extern cDisp;
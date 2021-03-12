#include "ChessDisplay.h"

using namespace sf;

class ChessPiece
{
public:
	int type;
	bool usable;
};




int main()
{
	RenderWindow window(VideoMode(800, 800), "Chess");
	Event event;

	//W = +
	//B = -
	/*
		pawn = 1
		knight = 2
		bishop = 3
		rook = 4
		king = 5
		queen = 6
	*/

	Texture circ, chessTexture;
	circ.loadFromFile("images/circle.png");
	chessTexture.loadFromFile("images/chessboard.png");
	int* selectedPiece = (int*)malloc(sizeof(int) * 2);
	int* oldselectedPiece = (int*)malloc(sizeof(int) * 2);

	//change int to actual chess piece class?
	int piece[8][8] = { { -4,-2,-3,-6,-5,-3,-2,-4 },
						{ -1,-1,-1,-1,-1,-1,-1,-1 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 1,1,1,1,1,1,1,1 },
						{ 4,2,3,6,5,3,2,4 } };



	Sprite chessboard(chessTexture);
	Sprite circle(circ);


	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				selectedPiece = cDisp.SetSelected(Mouse::getPosition(window));
				if (piece[selectedPiece[1]][selectedPiece[0]] != 0)
				{
					//board is upside down  ?????? fix pls k thx
					circle.setPosition(Vector2f(selectedPiece[0] * 100, selectedPiece[1] * 100));
					oldselectedPiece = selectedPiece;
				}
				else if (piece[oldselectedPiece[1]][oldselectedPiece[0]] != 0)
				{
					//just move the piece :muscle:
					int oldpiece = piece[oldselectedPiece[1]][oldselectedPiece[0]];
					piece[oldselectedPiece[1]][oldselectedPiece[0]] = 0;
					piece[selectedPiece[1]][selectedPiece[0]] = oldpiece;
				}
			}
		}


		//display stuff
		window.clear();
		window.draw(chessboard);
		window.draw(circle);
		cDisp.DisplayBoard(piece, window);
		window.display();
	}

	return 0;
}
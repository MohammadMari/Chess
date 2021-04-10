#include "ChessDisplay.h"
#include "ChessPiece.h"
#include <iostream>

using namespace sf;

const int side = 1; //set to one or negative one this is temporary and for testing only
bool turn = true; //again find a different way




bool isSide(int piece)
{
	if (piece < 0 && side < 0 && turn)
		return true;
	else if (piece > 0 && side > 0 && turn)
		return true;
	else if (piece < 0 && side > 0 && !turn)
		return true;
	else if (piece > 0 && side < 0 && !turn)
		return true;

	return false;
}

//check to see if the 
bool ValidMove(ChessPiece** board, int* oldSelected, int* newSelected)
{
	int difx = newSelected[0] - oldSelected[0];
	int dify = newSelected[1] - oldSelected[1];
	int xIt, yIt; //x and y iterator

	xIt = copysignf(1, difx);
	yIt = copysignf(1, dify);


	if (abs(difx) == abs(dify)) //moving diag
	{
		for (int i = 1; i < abs(dify); i++)
		{
			if (board[oldSelected[1] + (i * yIt)][oldSelected[0] + (i * xIt)].type != 0)
			{
				return false;
			}
		}
	}
	//moving straight
	else if (difx == 0)
	{
		for (int i = 1; i < abs(dify); i++)
		{
			if (board[oldSelected[1] + (i * yIt)][newSelected[0]].type != 0)
			{
				return false;
			}
		}
	}
	else if (dify == 0)
	{
		for (int i = 1; i < abs(difx); i++)
		{
			if (board[newSelected[1]][oldSelected[0] + (i * yIt)].type != 0)
			{
				return false;
			}
		}
	}

	//now to check for king check

	return true;
}


ChessPiece** Movement(ChessPiece** board, int* oldSelected, int* newSelected)
{
	//TODO make sure checked pieces cant move. What im thinking rn is to make a fake board with the move the player tried to make,
	//if king becomes checked then thats no good, just dont do it on the real board. there is prob a better way but this sounds easy.

	// Y = [1], X = [0]

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

	//pawn movement

	//old selected represents the second last piece/place the player selected
	// so it checks if its a pawn

	//remove valid spot checks, we're already checking for it now.
	if (abs(board[oldSelected[1]][oldSelected[0]].type) == 1 && ValidMove(board, oldSelected, newSelected))
	{
		//newSelected[1] is the Y axis, oldSelected[1] - board[oldSelected[1]][oldSelected[0]].type is used to evaluate what way the pawn moves up, if it is equal to one forward, its happy
		//oldSelected[0] == newSelected[0] is just saying its on the same X axis, hasn't moved left or right, checks to see if up ahead its empty.
		if (newSelected[1] == (oldSelected[1] - board[oldSelected[1]][oldSelected[0]].type) && newSelected[0] == oldSelected[0] && board[newSelected[1]][newSelected[0]].type == 0) //check for one space ahead
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[newSelected[1]][newSelected[0]].moved = true;
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
		//checks one square left and right, if either is selected it checks to see if the side selected is occupied by a player not on the same side.
		else if (newSelected[1] == (oldSelected[1] - board[oldSelected[1]][oldSelected[0]].type) && (newSelected[0] == (oldSelected[0] + 1) || newSelected[0] == (oldSelected[0] - 1)) && !isSide(board[newSelected[1]][newSelected[0]].type) && board[newSelected[1]][newSelected[0]].type) //check diag
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[newSelected[1]][newSelected[0]].moved = true;
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
		//first move pawn makes allows it to move up two spaces. This is for that.
		else if (!board[oldSelected[1]][oldSelected[0]].moved && newSelected[1] == (oldSelected[1] - (board[oldSelected[1]][oldSelected[0]].type * 2)) && newSelected[0] == oldSelected[0] && board[newSelected[1]][newSelected[0]].type == 0)//check for two spaces ahead
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[newSelected[1]][newSelected[0]].moved = true;
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
		//todo check for that french special case move
	}


	//knight movement
	if (abs(board[oldSelected[1]][oldSelected[0]].type) == 2)
	{
		//knights move either 2 X 1 Y or 1 X 2 Y. I just check to see if they move that much, make sure the space is empty or is an enemy and move it there.
		if (abs(newSelected[0] - oldSelected[0]) == 2 && abs(newSelected[1] - oldSelected[1]) == 1 && !isSide(board[newSelected[1]][newSelected[0]].type))
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
		else if (abs(newSelected[0] - oldSelected[0]) == 1 && abs(newSelected[1] - oldSelected[1]) == 2 && !isSide(board[newSelected[1]][newSelected[0]].type))
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
	}

	//bishop movement
	if (abs(board[oldSelected[1]][oldSelected[0]].type) == 3 && ValidMove(board, oldSelected, newSelected))
	{

		//bishops can only move diag. If they move the same amount of X and Y then its a valid move.
		if (abs(newSelected[0] - oldSelected[0]) == abs(newSelected[1] - oldSelected[1]) && !isSide(board[newSelected[1]][newSelected[0]].type))
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
	}

	//rook movement
	if (abs(board[oldSelected[1]][oldSelected[0]].type) == 4 && ValidMove(board, oldSelected, newSelected))
	{
		// X and Y movement
		if (abs(newSelected[0] - oldSelected[0]) == 0 || abs(newSelected[1] - oldSelected[1]) == 0)
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
	}


	//king movement
	if (abs(board[oldSelected[1]][oldSelected[0]].type) == 5 && ValidMove(board, oldSelected, newSelected))
	{

		//pasted straight from bishop.
		//made sure they can only move one square
		if ((abs(newSelected[0] - oldSelected[0]) == 1) && (abs(newSelected[1] - oldSelected[1]) == 1) && !isSide(board[newSelected[1]][newSelected[0]].type))
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
		else if ((abs(newSelected[0] - oldSelected[0]) == 0 && abs(newSelected[1] - oldSelected[1]) == 1) || (abs(newSelected[1] - oldSelected[1]) == 0 && abs(newSelected[0] - oldSelected[0]) == 1))
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
	}

	//queen movement
	if (abs(board[oldSelected[1]][oldSelected[0]].type) == 6 && ValidMove(board, oldSelected, newSelected))
	{
		//pasted straigt from bishop.
		if (abs(newSelected[0] - oldSelected[0]) == abs(newSelected[1] - oldSelected[1]) && !isSide(board[newSelected[1]][newSelected[0]].type))
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
		// X and Y movement
		else if (abs(newSelected[0] - oldSelected[0]) == 0 || abs(newSelected[1] - oldSelected[1]) == 0)
		{
			board[newSelected[1]][newSelected[0]] = board[oldSelected[1]][oldSelected[0]];
			board[oldSelected[1]][oldSelected[0]].Default();
			turn = !turn;
		}
	}


	return board;
}





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

	oldselectedPiece[0] = 50;
	oldselectedPiece[1] = 50;

	//change int to actual chess piece class?
	const int pieceLoc[8][8] = { { -4,-2,-3,-6,-5,-3,-2,-4 },
								{ -1,-1,-1,-1,-1,-1,-1,-1 },
								{ 0,0,0,0,0,0,0,0 },
								{ 0,0,0,0,0,0,0,0 },
								{ 0,0,0,0,0,0,0,0 },
								{ 0,0,0,0,0,0,0,0 },
								{ 1,1,1,1,1,1,1,1 },
								{ 4,2,3,6,5,3,2,4 } };

	//change to vector?
	ChessPiece** pieces = (ChessPiece**)malloc(8 * sizeof(ChessPiece));

	for (int i = 0; i < 8; i++)
	{
		pieces[i] = (ChessPiece*)malloc(8 * sizeof(ChessPiece));
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pieces[j][i].type = pieceLoc[j][i];
			pieces[j][i].moved = false;
		}
	}


	Sprite chessboard(chessTexture);
	Sprite circle(circ);
	bool draw = false;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				selectedPiece = cDisp.SetSelected(Mouse::getPosition(window));

				if (isSide(pieces[selectedPiece[1]][selectedPiece[0]].type))
					draw = true;
				else
					draw = false;

				if (isSide(pieces[selectedPiece[1]][selectedPiece[0]].type))
				{
					circle.setPosition(Vector2f(selectedPiece[0] * 100, selectedPiece[1] * 100));
					oldselectedPiece = selectedPiece;
				}
				else if (oldselectedPiece[0] != 50) //scuffed fix :)
				{
					if (!isSide(pieces[selectedPiece[1]][selectedPiece[0]].type))
					{
						pieces = Movement(pieces, oldselectedPiece, selectedPiece);
					}
				}
			}
		}


		//display stuff
		window.clear();
		window.draw(chessboard);
		if (draw)
			window.draw(circle);
		cDisp.DisplayBoard(pieces, window);
		window.display();
	}

	free(selectedPiece);
	free(oldselectedPiece);
	free(pieces);


	return 0;
}
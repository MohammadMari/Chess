#include "ChessDisplay.h"


using namespace std;

ChessDisplay cDisp;

void ChessDisplay::DisplayBoard(ChessPiece **piece, RenderWindow& window)
{
	Texture PW, PB, KW, KB, KnW, KnB, QW, QB, RW, RB, BW, BB;
	PW.loadFromFile("images/pawnw.png");
	PB.loadFromFile("images/pawnb.png");
	KW.loadFromFile("images/kingw.png");
	KB.loadFromFile("images/kingb.png");
	KnW.loadFromFile("images/knightw.png");
	KnB.loadFromFile("images/knightb.png");
	QW.loadFromFile("images/queenw.png");
	QB.loadFromFile("images/queenb.png");
	RW.loadFromFile("images/rookw.png");
	RB.loadFromFile("images/rookb.png");
	BW.loadFromFile("images/bishopw.png");
	BB.loadFromFile("images/bishopb.png");
	
	//makes sprites :)
	Sprite PawnW(PW);
	Sprite PawnB(PB);
	Sprite KingW(KW);
	Sprite KingB(KB);
	Sprite KnightW(KnW);
	Sprite KnightB(KnB);
	Sprite BishopW(BW);
	Sprite BishopB(BB);
	Sprite RookW(RW);
	Sprite RookB(RB);
	Sprite QueenW(QW);
	Sprite QueenB(QB);
	

	//draw pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (piece[i][j].type)
			{
			case 1: {
				PawnW.setPosition(Vector2f(j * 100, i * 100));
				window.draw(PawnW);
			} break;
			case -1: {
				PawnB.setPosition(Vector2f(j * 100, i * 100));
				window.draw(PawnB);
			} break;
			case 2: {
				KnightW.setPosition(Vector2f(j * 100, i * 100));
				window.draw(KnightW);
			} break;
			case -2: {
				KnightB.setPosition(Vector2f(j * 100, i * 100));
				window.draw(KnightB);
			} break;
			case 3: {
				BishopW.setPosition(Vector2f(j * 100, i * 100));
				window.draw(BishopW);
			} break;
			case -3: {
				BishopB.setPosition(Vector2f(j * 100, i * 100));
				window.draw(BishopB);
			} break;
			case 4: {
				RookW.setPosition(Vector2f(j * 100, i * 100));
				window.draw(RookW);
			} break;
			case -4: {
				RookB.setPosition(Vector2f(j * 100, i * 100));
				window.draw(RookB);
			} break;
			case 5: {
				KingW.setPosition(Vector2f(j * 100, i * 100));
				window.draw(KingW);
			} break;
			case -5: {
				KingB.setPosition(Vector2f(j * 100, i * 100));
				window.draw(KingB);
			} break;
			case 6: {
				QueenW.setPosition(Vector2f(j * 100, i * 100));
				window.draw(QueenW);
			} break;
			case -6: {
				QueenB.setPosition(Vector2f(j * 100, i * 100));
				window.draw(QueenB);
			} break;
			}
		}
	}
}

int* ChessDisplay::SetSelected(Vector2i location)
{
	int* selectedPiece = (int*)malloc(sizeof(int) * 2);
	selectedPiece[0] = floor(location.x / 100); 
	selectedPiece[1] = floor(location.y / 100);

	return selectedPiece;
}
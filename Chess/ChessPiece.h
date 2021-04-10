#pragma once
class ChessPiece
{
public:
	int type = 0;
	bool usable = true;
	bool moved = false;

	void Default()
	{
		type = 0;
		usable = true;
		moved = false;
	}
};
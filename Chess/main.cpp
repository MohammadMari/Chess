#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Title");
	Event event;

	Texture chessTexture;
	chessTexture.loadFromFile("images/chessboard.png");

	Sprite chessboard(chessTexture);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(chessboard);
		window.display();
	}
	
	return 0;
}
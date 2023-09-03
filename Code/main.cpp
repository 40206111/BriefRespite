#include "GameConfig.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

int main()
{
	std::string gameName = "It's Hard To Be A Bard v" + std::to_string(BriefRespite_VERSION_MAJOR) + '.' + std::to_string(BriefRespite_VERSION_MINOR);
	RenderWindow window(VideoMode(Vector2u(800, 600)), gameName);	//make window

	//Run game loop
	while (window.isOpen())
	{
		window.clear();	//clear window

		Event e;
		//pole events
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)	//close window
			{
				window.close();
			}
		}

		//get keyboard input
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.display();	//display window
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include "TankBase.h"
#include "Worldmap.h"

int main()
{
	Worldmap battleGorund("Res/backgound.png");

	sf::RenderWindow window(sf::VideoMode(battleGorund.getMapSize().x, battleGorund.getMapSize().y), "Tanks");
	window.setFramerateLimit(60);

	TankBase maus;
	sf::Event e;
	while(window.isOpen())
	{
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window.close();
			maus.getInput(e);
		}
		window.clear(sf::Color::White);
		battleGorund.draw(&window);
		maus.draw(&window);
		window.display();
	}
	return 0;
}
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Worldmap.h"

int main()
{
	Worldmap battleGorund("Res/backgound.png");

	sf::RenderWindow window(sf::VideoMode(battleGorund.getMapSize().x, battleGorund.getMapSize().y), "Tanks!");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	Tank maus(760 / 2, 500 / 2, 0);
	maus.setObstacles(battleGorund.getObstacles());
	sf::Event e;
	while(window.isOpen())
	{
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window.close();
			if(maus.getInput(e)) break;
		}
		window.clear(sf::Color::White);
		maus.update();
		battleGorund.draw(&window);
		maus.draw(&window);
		window.display();
	}
	return 0;
}
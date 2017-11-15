#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Worldmap.h"
typedef sf::Keyboard::Key button;

int main()
{
	Worldmap battleGorund("Res/backgound.png");

	sf::RenderWindow window(sf::VideoMode(battleGorund.getMapSize().x, battleGorund.getMapSize().y), "Tanks!!");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	std::vector<Tank *> tanks;

	Tank::ControlScheme 
		control1 = {
		sf::Keyboard::Key::W,
		sf::Keyboard::Key::S,
		sf::Keyboard::Key::A,
		sf::Keyboard::Key::D,
		sf::Keyboard::Key::Q,
		sf::Keyboard::Key::E,
		sf::Keyboard::Key::LShift,
		sf::Keyboard::Key::LControl,
		sf::Keyboard::Key::Space,
		sf::Keyboard::Key::L,
		sf::Keyboard::Key::LAlt
	},
		control2 = {
		button::Numpad8,
		button::Numpad5,
		button::Numpad4,
		button::Numpad6,
		button::Numpad7,
		button::Numpad9,
		button::Numpad1,
		button::Numpad0,
		button::Numpad2,
		button::RAlt,
		button::SemiColon
	};
	Tank maus(760 / 2, 500 / 2, 90, control1);
	tanks.push_back(&maus);

	/*
	*/
	Tank klaus(760 / 3, 300, 90, control2);
	klaus.setObstacles(battleGorund.getObstacles());
	tanks.push_back(&klaus);

	maus.setObstacles(battleGorund.getObstacles());
	maus.setEnemies(&tanks);
	/*
	*/
	klaus.setObstacles(battleGorund.getObstacles());
	klaus.setEnemies(&tanks);
	sf::Event e;
	while(window.isOpen())
	{
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window.close();
			if(maus.getInput(e)) break;
			if(klaus.getInput(e)) break;
		}
		window.clear(sf::Color::White);
		maus.update();
		klaus.update();
		battleGorund.draw(&window);
		maus.draw(&window);
		klaus.draw(&window);
		window.display();
	}
	return 0;
}
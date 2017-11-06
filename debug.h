#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
class debug
{
public:
	debug(int x, int y);
	void draw(sf::RenderWindow *w) const;
	~debug();
private:
	sf::CircleShape blob;
};


#include "debug.h"




debug::debug(int x, int y) :
	blob(10)
{
	blob.setPosition(x, y);
	blob.setOrigin(5, 5);
	blob.setFillColor(sf::Color::Yellow);
}

void debug::draw(sf::RenderWindow * w) const
{
	w->draw(blob);
}

debug::~debug()
{
}

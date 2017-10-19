#include "Obstacle.h"



Obstacle::Obstacle(int n, float *vertices)
{
	shape.setPrimitiveType(sf::TriangleStrip);
	shape.resize(n);
	for(int i = 0; i < n * 2; i += 2)
	{
		shape[i / 2].position = {*(vertices + i), *(vertices + i + 1)};
		shape[i / 2].color = sf::Color::Black;
	}
}

void Obstacle::draw(sf::RenderWindow * w) const
{
	w->draw(shape);
}


Obstacle::~Obstacle()
{
}

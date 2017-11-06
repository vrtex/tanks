#include "Obstacle.h"



Obstacle::Obstacle(int n, float *vertices)
{
	float xCentroid = 0, yCentroid = 0;
	logo.loadFromFile("Res/logo_small.png");
	flag.setTexture(logo);
	flag.setOrigin(logo.getSize().x / 2, logo.getSize().y / 2);
	flag.setScale(0.5, 0.5);
	shape.setPrimitiveType(sf::TriangleStrip);
	shape.resize(n);
	for(int i = 0; i < n * 2; i += 2)
	{
		xCentroid += *(vertices + i);
		yCentroid += *(vertices + i + 1);
		shape[i / 2].position = {*(vertices + i), *(vertices + i + 1)};
		shape[i / 2].color = sf::Color::Black;
	}
	xCentroid /= n;
	yCentroid /= n;
	flag.setPosition(xCentroid, yCentroid);
}

void Obstacle::draw(sf::RenderWindow * w) const
{
	w->draw(shape);
	w->draw(flag);
}


Obstacle::~Obstacle()
{
}

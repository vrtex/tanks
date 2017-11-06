#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class Obstacle
{
public:
	Obstacle(int n, float *vertices);
	void draw(sf::RenderWindow *w) const;
	~Obstacle();
private:
	sf::VertexArray shape;
	sf::Texture logo;
	sf::Sprite flag;
};


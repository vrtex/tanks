#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include "triangle.h"
class Obstacle
{
public:
	
	struct triangle
	{
		triangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
		float getSize();
		bool collidesWith(sf::Vector2f point);
		sf::Vector2f p1, p2, p3;
		float area;
	};
	
	Obstacle(int n, float *vertices);
	void showCoords();
	void draw(sf::RenderWindow *w) const;
	bool checkCollision(sf::RectangleShape &collider);
	~Obstacle();
private:
	sf::VertexArray shape;
	sf::Texture logo;
	sf::Sprite flag;
	std::vector<triangle> sections;
	float PI;
};


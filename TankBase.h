#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
class TankBase
{
public:
	TankBase();
	bool getInput(sf::Event &e);
	void draw(sf::RenderWindow *w) const;
	void setDirection();
	~TankBase();
private:
	sf::Sprite car;
	sf::Texture tex;

	float speed, rotateSpeed;
	sf::Vector2f direction;
	float PI;
};


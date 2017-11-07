#pragma once
#include "TankBase.h"
#include "TankTurret.h"
#include <SFML\Graphics.hpp>
class Obstacle;
class Tank
{
public:
	Tank(float x, float y, float r);
	bool getInput(sf::Event &e);
	void setObstacles(std::vector<Obstacle *> *obst);
	void update();
	void draw(sf::RenderWindow *w);
	~Tank();
private:
	TankTurret head;
	TankBase legs;
};


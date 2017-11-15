#pragma once
#include "TankBase.h"
#include "TankTurret.h"
#include <SFML\Graphics.hpp>
class Obstacle;
class Tank
{
public:
	struct ControlScheme
	{
		sf::Keyboard::Key up;
		sf::Keyboard::Key down;
		sf::Keyboard::Key left;
		sf::Keyboard::Key right;
		sf::Keyboard::Key turretLeft;
		sf::Keyboard::Key turretRight;
		sf::Keyboard::Key turretUp;
		sf::Keyboard::Key turretDown;
		sf::Keyboard::Key shoot;
		sf::Keyboard::Key lights;
		sf::Keyboard::Key lightsMode;
	};
	Tank(float x, float y, float r, Tank::ControlScheme &control);
	bool getInput(sf::Event &e);
	void setObstacles(std::vector<Obstacle *> *obst);
	void setEnemies(std::vector<Tank *> *t);
	bool collidesWithTank(TankBase &other);
	void update();
	void draw(sf::RenderWindow *w);
	~Tank();
private:
	TankTurret head;
	TankBase legs;
	ControlScheme controls;
};


#include "Tank.h"
#include "Obstacle.h"



Tank::Tank(float x, float y, float r, Tank::ControlScheme &control) :
	head({x, y}, r, 
	{
		control.turretUp,
		control.turretDown,
		control.turretLeft,
		control.turretRight,
		control.shoot
	}),
	legs({x, y}, r, &head,
	{
		control.up,
		control.down,
		control.left,
		control.right,
		control.lights,
		control.lightsMode
	}),
	controls(control)
{
	head.connect(&legs);
}

bool Tank::getInput(sf::Event & e)
{
	if(legs.getInput(e)) return true;
	else if(head.getInput(e)) return true;
	return false;
}

void Tank::setObstacles(std::vector<Obstacle*> *obst)
{
	legs.setObstacles(obst);
}

void Tank::setEnemies(std::vector<Tank*>* t)
{
	legs.setEnemies(t);
}

bool Tank::collidesWithTank(TankBase & other)
{
	return legs.collidesWithTank(other);
}

void Tank::update()
{
	head.update();
	legs.update();
}


void Tank::draw(sf::RenderWindow * w)
{
	legs.draw(w);
	head.draw(w);
	legs.showDiodes(w);
}

Tank::~Tank()
{
}

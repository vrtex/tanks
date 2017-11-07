#include "Tank.h"
#include "Obstacle.h"



Tank::Tank(float x, float y, float r) :
	head({x, y}, r), legs({x, y}, r, &head)
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

#include "TankBase.h"



TankBase::TankBase()
{
	tex.loadFromFile("Res/coon_base_small_small.png");
	car.setTexture(tex);
	car.setOrigin((float)tex.getSize().x / 2, (float)tex.getSize().y / 2);
	//car.setScale(0.25, 0.25);
	car.setPosition(760 / 2, 500 / 2);
	speed = 5;
	rotateSpeed = 1;
	PI = (float)acos(-1);
}

bool TankBase::getInput(sf::Event &e)
{
	if(e.type == sf::Event::KeyPressed)
	switch(e.key.code)
	{
	case sf::Keyboard::D:
		car.rotate(rotateSpeed);
		setDirection();
		return true;
	case sf::Keyboard::A:
		car.rotate(-rotateSpeed);
		setDirection();
		return true;
	case sf::Keyboard::W:
		car.move((float)direction.x * speed, (float)direction.y * speed);
		setDirection();
		return true;
	case sf::Keyboard::S:
		car.move((float)direction.x * speed * 0.75, (float)direction.y * speed * 0.75);
		setDirection();
		return true;
	default:
		break;
	}
	return false;
}

void TankBase::draw(sf::RenderWindow * w) const
{
	w->draw(car);
}

void TankBase::setDirection()
{
	direction = {cos(car.getRotation() * PI / 180), sin(car.getRotation() * PI / 180)};
}


TankBase::~TankBase()
{
}

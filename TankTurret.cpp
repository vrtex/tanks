#include "TankTurret.h"
#include "TankBase.h"


TankTurret::TankTurret(sf::Vector2f pos, float rot, TurretControl cntr) :
	buttons(cntr)
{
	legs = nullptr;
	tex.loadFromFile("Res/turret_small_small.png");
	tex.setSmooth(true);
	turret.setTexture(tex);
	turret.setOrigin(20, tex.getSize().y / 2);
	turret.setPosition(pos);
	turret.setRotation(rot);

	absoluteRotation = rot;
	currentPosition = 0;
	rotateSpeed = 1;
	currentRotation = 0;
	PI = (float)acos(-1);
	setDirection();
	shootingForce = 15;
	minimumRange = 150;
	leanStep = 0.05;
	lean = 0.5f;
	cooldown = 200;
	cooldownTimer.restart();
	setRange();
}

void TankTurret::connect(TankBase *l)
{
	legs = l;
}

bool TankTurret::getInput(sf::Event & e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		if(e.key.code == buttons.turretLeft)
		{
			currentRotation = -rotateSpeed;
			return true;
		}
		if(e.key.code == buttons.turretRight)
		{
			currentRotation = rotateSpeed;
			return true;
		}
		if(e.key.code == buttons.shoot)
		{
			shoot();
			return true;
		}
		if(e.key.code == buttons.turretUp)
		{
			setRange(leanStep);
			return true;
		}
		if(e.key.code == buttons.turretDown)
		{
			setRange(-leanStep);
			return true;
		}
	}

	if(e.type == sf::Event::KeyReleased)
	{
		if(e.key.code == buttons.turretLeft || e.key.code == buttons.turretRight)
		{
			currentRotation = 0;
			return true;
		}
	}
	return false;
}


void TankTurret::update()
{
	if(currentPosition + currentRotation >= -90 && currentPosition + currentRotation <= 90)
	{
		currentPosition += currentRotation;
		absoluteRotation = (int)(absoluteRotation + currentRotation + 360) % 360;
		turret.rotate(currentRotation);
		setDirection();
	}
}

void TankTurret::draw(sf::RenderWindow * w) const
{
	w->draw(turret);
	for(auto &c : craters)
	{
		c->draw(w);
	}
}

void TankTurret::move(sf::Vector2f d)
{
	turret.move(d);
}

void TankTurret::setRange(float step)
{
	if(fabs(step) > 0.001)
	{
		if(lean + step > 1)
			lean = 1;
		else if(lean + step < 0)
			lean = 0;
		else lean += step;
	}
	shootingRange = shootingForce * shootingForce * sin(2 * lean) + minimumRange;
	std::cout << lean << "\n";
}

void TankTurret::shoot()
{
	if(cooldownTimer.getElapsedTime().asMilliseconds() < cooldown) return;
	craters.push_back(new debug(
		shootingDirection.x * shootingRange + turret.getPosition().x, 
		shootingDirection.y * shootingRange + turret.getPosition().y));
	cooldownTimer.restart();
}

void TankTurret::baseRotation(float r)
{
	turret.rotate(r);
	absoluteRotation = (int)(absoluteRotation + r + 360) % 360;
	setDirection();
}

void TankTurret::setDirection()
{
	shootingDirection = {cos(absoluteRotation * PI / 180), sin(absoluteRotation * PI / 180)};
}

TankTurret::~TankTurret()
{
	for(auto &c : craters)
	{
		delete c;
	}
}

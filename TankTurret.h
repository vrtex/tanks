#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include "debug.h"
class TankBase;
class TankTurret
{
public:
	struct TurretControl
	{
		sf::Keyboard::Key
			turretUp,
			turretDown,
			turretLeft,
			turretRight,
			shoot;
	};
public:
	TankTurret(sf::Vector2f pos, float rot, TurretControl cntr);
	void connect(TankBase *l);
	bool getInput(sf::Event &e);
	void update();
	void draw(sf::RenderWindow *w) const;
	void move(sf::Vector2f d);
	void setRange(float step = 0);
	void shoot();
	void baseRotation(float r);
	void setDirection();
	~TankTurret();
private:
	std::vector<debug *> craters;
	TankBase *legs;
	sf::Texture tex;
	sf::Sprite turret;

	float currentPosition, absoluteRotation;
	float currentRotation;
	float rotateSpeed;
	float lean;		//in radians
	float leanStep;
	float minimumRange;
	sf::Vector2f shootingDirection;
	float shootingForce;
	float shootingRange;
	int cooldown;
	sf::Clock cooldownTimer;

	TurretControl buttons;

	float PI;
};


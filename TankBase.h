#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include "TankTurret.h"

class Obstacle;
class TankBase
{
private:
	struct diode
	{
		diode(sf::Vector2f pos);
		void setOffset(sf::Vector2f position);
		void move(sf::Vector2f dir);
		void draw(sf::RenderWindow *w);
		void flipSwitch();
		void rotate(float angle);
		sf::CircleShape blob;
		sf::Color onColor, offColor;
		float size;
		bool on;
	};

public:
	TankBase(sf::Vector2f pos, int rot, TankTurret *h);
	bool getInput(sf::Event &e);
	void update();
	void draw(sf::RenderWindow *w);
	void showDiodes(sf::RenderWindow *w);
	void setDirection();
	float getDirection() const;
	void setObstacles(std::vector<Obstacle *> *obst);
	~TankBase();
private:
	TankTurret *head;
	sf::Sprite car;
	sf::Texture tex;
	sf::RectangleShape hitbox;
	sf::Vector2f halfSize;
	diode leftDiode, rightDiode, backDiode;
	bool blinking;
	sf::Clock blinkTimer;

	float currentSpeed, currentRotation;
	float speed, rotateSpeed;
	const float backPenalty = 0.75;
	sf::Vector2f direction;

	std::vector<Obstacle *> *obstacles;
	float PI;
};


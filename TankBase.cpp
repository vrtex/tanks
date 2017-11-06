#include "TankBase.h"



TankBase::TankBase(sf::Vector2f pos, int rot, TankTurret *h) :
	backDiode(pos), leftDiode(pos), rightDiode(pos)
{
	head = h;
	tex.loadFromFile("Res/coon_base_small_small.png");
	tex.setSmooth(true);
	car.setTexture(tex);
	car.setOrigin((float)tex.getSize().x / 2, (float)tex.getSize().y / 2);
	//car.setScale(0.25, 0.25);
	car.setPosition(pos);
	car.setRotation(rot);
	setDirection();
	currentRotation = 0;
	currentSpeed = 0;
	speed = 3;
	rotateSpeed = 2;
	hitbox.setFillColor(sf::Color::Magenta);
	hitbox.setRadius(sqrt(tex.getSize().x * tex.getSize().x / 4 + tex.getSize().y * tex.getSize().y / 4));
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setPosition(pos);
	halfSize = (sf::Vector2f)tex.getSize();

	
	backDiode.setOffset(sf::Vector2f(-30, 0));
	leftDiode.setOffset(sf::Vector2f(20, -15));
	rightDiode.setOffset(sf::Vector2f(20, 15));
	blinkTimer.restart();
	blinking = false;
	PI = (float)acos(-1);
}

bool TankBase::getInput(sf::Event &e)
{
	if(e.type == sf::Event::KeyPressed)
		switch(e.key.code)
		{
		case sf::Keyboard::D:
			currentRotation = rotateSpeed;
			return true;
		case sf::Keyboard::A:
			currentRotation = -rotateSpeed;
			return true;
		case sf::Keyboard::W:
			currentSpeed = speed;
			return true;
		case sf::Keyboard::S:
			currentSpeed = -speed * backPenalty;
			return true;
		case sf::Keyboard::L:
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
			{
				blinking = !blinking;
				blinkTimer.restart();
				break;
			}
			blinking = false;
			backDiode.flipSwitch();
			leftDiode.flipSwitch();
			rightDiode.flipSwitch();
			break;
		default:
			break;
		}
	else if(e.type == sf::Event::KeyReleased)
		switch(e.key.code)
		{
		case sf::Keyboard::D:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				currentRotation = 0;
			return true;
		case sf::Keyboard::A:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				currentRotation = 0;
			return true;
		case sf::Keyboard::W:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				currentSpeed = 0;
			return true;
		case sf::Keyboard::S:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				currentSpeed = 0;
			return true;
		default:
			break;
		}
	return false;
}

void TankBase::update()
{
	if(blinking && blinkTimer.getElapsedTime().asMilliseconds() > 500)
	{
		backDiode.flipSwitch();
		leftDiode.flipSwitch();
		rightDiode.flipSwitch();
		blinkTimer.restart();
	}
	car.rotate(currentRotation);
	head->baseRotation(currentRotation);
	if(fabs(currentRotation) > rotateSpeed * 0.5) setDirection();
	backDiode.rotate(currentRotation);
	leftDiode.rotate(currentRotation);
	rightDiode.rotate(currentRotation);

	car.move(direction * currentSpeed);
	hitbox.move(direction * currentSpeed);
	head->move(direction * currentSpeed);
	backDiode.move(direction * currentSpeed);
	leftDiode.move(direction * currentSpeed);
	rightDiode.move(direction * currentSpeed);
	
	backDiode.update();
}

void TankBase::draw(sf::RenderWindow * w)
{
	//w->draw(hitbox);
	w->draw(car);

	backDiode.draw(w);
	leftDiode.draw(w);
	rightDiode.draw(w);
}

void TankBase::setDirection()
{
	direction = {cos(car.getRotation() * PI / 180), sin(car.getRotation() * PI / 180)};
}

float TankBase::getDirection() const
{
	return car.getRotation();
}


TankBase::~TankBase()
{
}

TankBase::diode::diode(sf::Vector2f pos)
{
	onColor = sf::Color::Red;
	offColor = sf::Color::Transparent;
	size = 5;
	blob.setRadius(5);
	blob.setPosition(pos);
	blob.setFillColor(onColor);
}

void TankBase::diode::setOffset(sf::Vector2f position)
{
	sf::Vector2f clip(size, size);
	blob.setOrigin(clip - position);
}

void TankBase::diode::move(sf::Vector2f dir)
{
	blob.move(dir);
}

void TankBase::diode::draw(sf::RenderWindow * w)
{
	w->draw(blob);
}

void TankBase::diode::flipSwitch()
{
	on = !on;
	if(on) blob.setFillColor(onColor);
	else blob.setFillColor(offColor);
}

void TankBase::diode::update()
{

}

void TankBase::diode::rotate(float angle)
{
	blob.rotate(angle);
}

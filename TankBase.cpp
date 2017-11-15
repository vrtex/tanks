#include "TankBase.h"
#include "Obstacle.h"
#include "Tank.h"


TankBase::TankBase(sf::Vector2f pos, int rot, TankTurret *h, CarControl ctrl) :
	backDiode(pos), leftDiode(pos), rightDiode(pos), buttons(ctrl)
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
	speed = 1.2;
	rotateSpeed = 2;
	hitbox.setFillColor(sf::Color::Magenta);
	sf::Vector2f hitboxSize(tex.getSize().x + 25, tex.getSize().y + 25);
	hitbox.setSize(hitboxSize);
	hitbox.setOrigin(hitboxSize.x / 2, hitboxSize.y / 2);
	hitbox.setPosition(pos);
	hitbox.rotate(rot);

	halfSize = (sf::Vector2f)tex.getSize();
	
	backDiode.setOffset(sf::Vector2f(-30, 0));
	leftDiode.setOffset(sf::Vector2f(20, -15));
	rightDiode.setOffset(sf::Vector2f(20, 15));
	backDiode.rotate(rot);
	leftDiode.rotate(rot);
	rightDiode.rotate(rot);
	blinkTimer.restart();
	blinking = false;

	obstacles = nullptr;
	PI = (float)acos(-1);
}

bool TankBase::getInput(sf::Event &e)
{
	if(e.type == sf::Event::KeyPressed)

	{
		if(e.key.code == buttons.right)
		{
			currentRotation = rotateSpeed;
			return true;
		}
		if(e.key.code == buttons.left)
		{
			currentRotation = -rotateSpeed;
			return true;
		}
		if(e.key.code == buttons.up)
		{
			currentSpeed = speed;
			return true;
		}
		if(e.key.code == buttons.down)
		{
			currentSpeed = -speed * backPenalty;
			return true;
		}
		if(e.key.code == buttons.lights)
		{
			if(sf::Keyboard::isKeyPressed(buttons.lightsMode))
			{
				blinking = !blinking;
				blinkTimer.restart();
				return true;
			}
			blinking = false;
			backDiode.flipSwitch();
			leftDiode.flipSwitch();
			rightDiode.flipSwitch();
			return true;
		}
		
	}
	if(e.type == sf::Event::KeyReleased)
	{
		if(e.key.code == buttons.right)
		{
			currentRotation = 0;
			return true;
		}
		if(e.key.code == buttons.left)
		{
			currentRotation = -0;
			return true;
		}
		if(e.key.code == buttons.up)
		{
			currentSpeed = 0;
			return true;
		}
		if(e.key.code == buttons.down)
		{
			currentSpeed = 0;
			return true;
		}
	}
	return false;
}

void TankBase::update()
{
	bool clearPath = true;
	if(blinking && blinkTimer.getElapsedTime().asMilliseconds() > 500)
	{
		backDiode.flipSwitch();
		leftDiode.flipSwitch();
		rightDiode.flipSwitch();
		blinkTimer.restart();
	}
	hitbox.move(direction * (currentSpeed));
	hitbox.rotate(currentRotation);
	for(int i = 0; i < obstacles->size(); ++i)
	{
		if(obstacles->at(i)->checkCollision(hitbox))
		{
			//obstacles->at(i)->showCoords();
			clearPath = false;
			break;
		}
	}
	if(clearPath)
		for(auto &e : *tanks)
		{
			if(e->collidesWithTank(*this))
			clearPath = false;
		}
	if(clearPath)
	{
		car.rotate(currentRotation);
		head->baseRotation(currentRotation);
		if(fabs(currentRotation) > rotateSpeed * 0.5) setDirection();
		backDiode.rotate(currentRotation);
		leftDiode.rotate(currentRotation);
		rightDiode.rotate(currentRotation);
		car.move(direction * currentSpeed);
		head->move(direction * currentSpeed);
		backDiode.move(direction * currentSpeed);
		leftDiode.move(direction * currentSpeed);
		rightDiode.move(direction * currentSpeed);
	}
	else
	{
		hitbox.move(-direction * (currentSpeed));
		hitbox.rotate(-currentRotation);
	}

}

void TankBase::draw(sf::RenderWindow * w)
{
	w->draw(hitbox);
	w->draw(car);
}

bool TankBase::collidesWithTank(TankBase & other)
{
	if(this == &other) return false;
	sf::Vector2f points1[4], points2[4];
	float rotation = hitbox.getRotation() * PI / 180;
	for(int i = 0; i < 4; ++i)
	{
		points1[i].x = (hitbox.getPoint(i).x - hitbox.getOrigin().x) * cos(rotation) - (hitbox.getPoint(i).y - hitbox.getOrigin().y) * sin(rotation);
		points1[i].x += hitbox.getPosition().x;
		points1[i].y = (hitbox.getPoint(i).x - hitbox.getOrigin().x) * sin(rotation) + (hitbox.getPoint(i).y - hitbox.getOrigin().y) * cos(rotation);
		points1[i].y += hitbox.getPosition().y;
	}
	rotation = other.hitbox.getRotation() * PI / 180;
	for(int i = 0; i < 4; ++i)
	{
		points2[i].x = (other.hitbox.getPoint(i).x - other.hitbox.getOrigin().x) * cos(rotation) - (other.hitbox.getPoint(i).y - other.hitbox.getOrigin().y) * sin(rotation);
		points2[i].x += other.hitbox.getPosition().x;
		points2[i].y = (other.hitbox.getPoint(i).x - other.hitbox.getOrigin().x) * sin(rotation) + (other.hitbox.getPoint(i).y - other.hitbox.getOrigin().y) * cos(rotation);
		points2[i].y += other.hitbox.getPosition().y;
	}
	Obstacle::triangle t1(points1[0], points1[1], points1[2]);
	Obstacle::triangle t2(points1[0], points1[1], points1[3]);

	Obstacle::triangle t3(points2[0], points2[1], points2[3]);
	Obstacle::triangle t4(points2[0], points2[1], points2[3]);
	for(int i = 0; i < 4; ++i)
	{
		if(t1.collidesWith(points2[i])) return true;
		if(t2.collidesWith(points2[i])) return true;
	}
	for(int i = 0; i < 4; ++i)
	{
		if(t3.collidesWith(points1[i])) return true;
		if(t4.collidesWith(points1[i])) return true;
	}
	return false;
}

void TankBase::showDiodes(sf::RenderWindow * w)
{
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

void TankBase::setObstacles(std::vector<Obstacle*> *obst)
{
	obstacles = obst;
}

void TankBase::setEnemies(std::vector<Tank*>* t)
{
	tanks = t;
	std::cout << tanks->size() << "\n";
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


void TankBase::diode::rotate(float angle)
{
	blob.rotate(angle);
}

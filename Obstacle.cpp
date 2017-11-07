#include "Obstacle.h"



Obstacle::Obstacle(int n, float *vertices)
{
	float xCentroid = 0, yCentroid = 0;
	logo.loadFromFile("Res/logo_small.png");
	flag.setTexture(logo);
	flag.setOrigin(logo.getSize().x / 2, logo.getSize().y / 2);
	flag.setScale(0.5, 0.5);
	shape.setPrimitiveType(sf::TriangleStrip);
	shape.resize(n);
	for(int i = 0; i < n * 2; i += 2)
	{
		if(i >= 4)
		{
			sections.emplace_back(sf::Vector2f(*(vertices + i), *(vertices + i + 1)), 
				sf::Vector2f(*(vertices + i - 2), *(vertices + i + 1 - 2)),
				sf::Vector2f(*(vertices + i - 4), *(vertices + i + 1 - 4)));
		}
		xCentroid += *(vertices + i);
		yCentroid += *(vertices + i + 1);
		shape[i / 2].position = {*(vertices + i), *(vertices + i + 1)};
		shape[i / 2].color = sf::Color::Black;
	}
	xCentroid /= n;
	yCentroid /= n;
	flag.setPosition(xCentroid, yCentroid);
	PI = (float)acos(-1);
}

void Obstacle::draw(sf::RenderWindow * w) const
{
	w->draw(shape);
	w->draw(flag);
}

bool Obstacle::checkCollision(sf::RectangleShape & collider)
{
	float rotation = collider.getRotation() * PI / 180;
	sf::Vector2f points[4];
	for(int i = 0; i < 4; ++i)
	{
		points[i].x = (collider.getPoint(i).x - collider.getOrigin().x) * cos(rotation) - (collider.getPoint(i).y - collider.getOrigin().y) * sin(rotation);
		points[i].x += collider.getPosition().x;
		points[i].y = (collider.getPoint(i).x - collider.getOrigin().x) * sin(rotation) + (collider.getPoint(i).y - collider.getOrigin().y) * cos(rotation);
		points[i].y += collider.getPosition().y;
	}
	triangle collider1(points[0], points[1], points[2]), collider2(points[0], points[3], points[2]);

	for(int i = 0; i < sections.size(); ++i)
	{
		for(int p = 0; p < 4; ++p)
		{
			if(sections.at(i).collidesWith(points[p])) return true;
		}
		if(collider1.collidesWith(sections.at(i).p1) ||
			collider2.collidesWith(sections.at(i).p1) ||
			collider1.collidesWith(sections.at(i).p2) ||
			collider2.collidesWith(sections.at(i).p2) ||
			collider1.collidesWith(sections.at(i).p3) ||
			collider2.collidesWith(sections.at(i).p3)) return true;

	}
	return false;
}


Obstacle::~Obstacle()
{
}

Obstacle::triangle::triangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3):
	p1(p1), p2(p2), p3(p3)
{
	area = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	area /= 2;
	if(area < 0) area = -area;
}

float Obstacle::triangle::getSize()
{
	return area;
}

bool Obstacle::triangle::collidesWith(sf::Vector2f point)
{
	triangle t1(p1, p2, point), t2(p1, point, p3), t3(point, p2, p3);
	if(t1.getSize() + t2.getSize() + t3.getSize() > area) return false;
	return true;
}

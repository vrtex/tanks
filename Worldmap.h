#pragma once
#include <SFML\Graphics.hpp>
#include "Obstacle.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Worldmap
{
public:
	Worldmap(std::string mapFile);
	void draw(sf::RenderWindow *w) const;
	void loadObstacle(int n, float *v);
	sf::Vector2f getMapSize() const;
	~Worldmap();
private:
	sf::Texture mapTexture;
	sf::Sprite battleGround;
	sf::VertexArray debugGrid;

	std::vector<Obstacle *> obstacles;
	
};


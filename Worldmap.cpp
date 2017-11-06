#include "Worldmap.h"



Worldmap::Worldmap(std::string mapFile)
{
	mapTexture.loadFromFile(mapFile);
	battleGround.setTexture(mapTexture);

	std::ifstream obstacleFile;
	obstacleFile.open("Res/obstacles.txt");
	int m;
	obstacleFile >> m;
	int n;
	float *table;
	for(int j = 0; j < m; ++j)
	{
		obstacleFile >> n;
		table = new float[n * sizeof(float)];
		for(int i = 0; i < n * 2; i += 2)
		{
			obstacleFile >> *(table + i);
			obstacleFile >> *(table + i + 1);
		}
		loadObstacle(n, table);
		delete[] table;
	}

	obstacleFile.close();

	debugGrid.setPrimitiveType(sf::Lines);
	for(unsigned int i = 100; i < mapTexture.getSize().x; i += 100)
	{
		debugGrid.append(sf::Vertex({(float)i, 0}));
		debugGrid.append(sf::Vertex({(float)i, (float)mapTexture.getSize().y}));
	}
	for(unsigned int i = 100; i < mapTexture.getSize().y; i += 100)
	{
		debugGrid.append(sf::Vertex({0, (float)i}));
		debugGrid.append(sf::Vertex({(float)mapTexture.getSize().x, (float)i}));
	}
}

void Worldmap::draw(sf::RenderWindow * w) const
{
	w->draw(battleGround);
	for(auto &o : obstacles)
	{
		o->draw(w);
	}
}

void Worldmap::loadObstacle(int n, float * v)
{
	obstacles.push_back(new Obstacle(n, v));
}

sf::Vector2f Worldmap::getMapSize() const
{
	return (sf::Vector2f)mapTexture.getSize();
}


Worldmap::~Worldmap()
{
}

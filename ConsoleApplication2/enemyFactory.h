#pragma once
#include "obstacle.h"
#include "runner.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <cmath>  /*need mostly for the sqrt*/

struct Enemy {
	sf::Vector2i sheetLoc;
	sf::Vector2i dim;
	sf::Vector2i pos;
	sf::Texture spMap;
	double scale;
	int aniLength;
	int r;
	Enemy(sf::Vector2i sheetLoc, sf::Vector2i dim, sf::Vector2i pos,
		sf::Texture &spMap, double scale, int aniLength, int r);
};

class EnemyFactory {
	sf::Clock c;
	std::vector<Obstacle> enemies;
	std::vector<Enemy> enemiesInfo;
	sf::Texture spMap;
	// groundlevel as in elevataion
	int groundLevel;
	// level as in a game level 
	int level = 0;
	bool hitTest(int x1, int y1, int r1, int x2, int y2, int r2);
public:
	//takes a texture and a vector of enemy struct will use this to set up all obstacles in game
	EnemyFactory(sf::Texture &t, std::vector<Enemy> &eI);
	void draw(sf::RenderWindow &window);
	void update();
	bool pubHitTest(Runner &r);
};


#include "enemyFactory.h"
#include <iostream>

//Enemy stuct, constructor
Enemy::Enemy(sf::Vector2i sheetLoc, sf::Vector2i dim, sf::Vector2i pos,
	sf::Texture &spMap, double scale, int aniLength, int r) : sheetLoc{ sheetLoc },
	dim{ dim }, pos{ pos }, spMap{ spMap }, scale{ scale }, aniLength{ aniLength },  
	r {r} 
{}

EnemyFactory::EnemyFactory(sf::Texture &t, std::vector<Enemy> &eI) : spMap{ t }, enemiesInfo { eI } {
	
	srand(time(NULL));
	int n = rand() % enemiesInfo.size();
	
	//Obstacle(int x, int y, int speed, double scale, sf::Texture &t, int aniLength, int w, int h, int startx, int starty);
	
	//had an error ealier b/c i was stupid and didn't define obs a proper copy/mv constructor
	enemies.emplace_back(Obstacle{ 750, enemiesInfo[n].pos.y, 5, enemiesInfo[n].scale, spMap,  enemiesInfo[n].aniLength,
		enemiesInfo[n].dim.x, enemiesInfo[n].dim.y, enemiesInfo[n].sheetLoc.x, enemiesInfo[n].sheetLoc.y, enemiesInfo[n].r });
	n = rand() % enemiesInfo.size();
	enemies.emplace_back( Obstacle{ 1250, enemiesInfo[n].pos.y, 5, enemiesInfo[n].scale, spMap,  enemiesInfo[n].aniLength,
		enemiesInfo[n].dim.x, enemiesInfo[n].dim.y, enemiesInfo[n].sheetLoc.x, enemiesInfo[n].sheetLoc.y, enemiesInfo[n].r });

	std::cout << enemiesInfo[0].sheetLoc.y << std::endl;

}

//use pythagoras theorem for a simple circle hitTest
bool EnemyFactory::hitTest(int x1, int y1, int r1, int x2, int y2, int r2) {
	float w = x1 - x2;
	float h = y1 - y2;

	if (sqrt(w * w + h * h) < r1 + r2) {
	//	std::cout << "hit" << std::endl;
		return true;
	}
	return false;
}

bool EnemyFactory::pubHitTest(Runner &r) {
	for (int i = 0; i < enemies.size(); i++) {

		if (hitTest(enemies[i].getCenter().x, enemies[i].getCenter().y, enemies[i].getRadius(),
			r.getCenter().x, r.getCenter().y, r.getRadius())) {

			return true;
		}
	}
	return false;
}

void EnemyFactory::draw(sf::RenderWindow &window) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].draw(window);
	}
}

void EnemyFactory::update() {
	srand(time(NULL));
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].update()) {
			//void changeForm(int aL, double scale, int newY, sf::Vector2i boxPos, sf::Vector2i dim);
			// gets a new form (should work hopefully lol
			int n = rand() % enemiesInfo.size();
			enemies[i].changeForm(enemiesInfo[n].aniLength, enemiesInfo[n].scale, enemiesInfo[n].pos.y,
				enemiesInfo[n].sheetLoc, enemiesInfo[n].dim);
		}
	}
}
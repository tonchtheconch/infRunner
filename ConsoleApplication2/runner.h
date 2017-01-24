#pragma once
#ifndef RUNNER_H
#define RUNNER_H
#include <SFML/Graphics.hpp>

class Runner {
	int x;
	int y;
	int r; 
	int frame = 0;
	int framecount = 0;
	sf::Texture t;
	sf::Sprite mc;
	sf::Vector2i animations[6];
	sf::Vector2i center;
	bool notHit = true;
	int timer = 0;
public:
	Runner(int x, int y, sf::Texture &t);
	Runner(int x, int y, int r, sf::Texture &t);
	sf::Vector2i getCenter();
	int getRadius();
	bool jump();
	void draw(sf::RenderWindow &window);
	void setNotHit(bool hit);
};

#endif // !1
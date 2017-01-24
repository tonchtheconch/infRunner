#pragma once
#ifndef _BG_
#define _BG_
#include <SFML/Graphics.hpp>

class BG {
	int x1;
	int x2;
	int y = 0;
	int width;
	int speed;
	sf::Texture Layer;
	sf::Sprite img1;
	sf::Sprite img2;
public:
	BG(sf::Texture &Layer, int speed, int width, float scale);
	void draw(sf::RenderWindow &window);
	void scroll();
};


#endif // !_BG_

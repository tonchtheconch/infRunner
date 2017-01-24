#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include <utility>  
#include <SFML/Graphics.hpp>

class Obstacle {
	int x = 1000;
	int y = 175;
	int w, h;
	int speed; 
	int aniLength;
	int frame = 0;
	int framecount = 0;
	double scale;

	sf::Vector2i center;
	int r;

	sf::Texture t;
	sf::Sprite ob;
	sf::Vector2i *animations;
public:
	//Obstacle(int x, int y, int speed, sf::Color c, sf::Vector2f v);
	Obstacle(int x, int y, int speed, double scale, sf::Texture &t,
		int aniLength, int w, int h, int startx, int starty);
	Obstacle(int x, int y, int speed, double scale, sf::Texture &t,
		int aniLength, int w, int h, int startx, int starty, int r);
	//Obstacle(int speed, sf::Color c, sf::Vector2f v);
	Obstacle(const Obstacle &other);
	Obstacle &operator=(Obstacle &&other);
	bool update();
	void draw(sf::RenderWindow &window);
	void setSpeed(int s);
	void changeForm(int aL, double scale, int newY, sf::Vector2i boxPos, sf::Vector2i dim);
	sf::Vector2i getCenter();
	int getRadius();
	~Obstacle();
};

#endif // !1
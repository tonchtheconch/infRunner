#include "obstacle.h"
#include <iostream>

using namespace std;

Obstacle::Obstacle(int x, int y, int speed, double scale, 
	sf::Texture &t, int aniLength, int w, int h, int startx, int starty) :
	x{ x }, y{ y }, speed{ speed }, t{ t }, w{ w }, 
	h{ h }, aniLength{ aniLength }, scale{ scale } {

	animations = new sf::Vector2i[aniLength];
	for (int i = 0; i < aniLength; i++) {
		animations[i] = sf::Vector2i(startx, starty + i * h);
	}

	center.x = x + w * scale / 2;
	center.y = y + h * scale / 2;

	t.setSmooth(true);
	ob.setTexture(t);
	ob.setPosition(x, y);
	ob.setScale(scale, scale);
}

Obstacle::Obstacle(int x, int y, int speed, double scale,
	sf::Texture &t, int aniLength, int w, int h, int startx, int starty, int r) :
	x{ x }, y{ y }, speed{ speed }, t{ t }, w{ w },
	h{ h }, aniLength{ aniLength }, scale{ scale }, r{ r } {

	animations = new sf::Vector2i[aniLength];
	for (int i = 0; i < aniLength; i++) {
		animations[i] = sf::Vector2i(startx, starty + i * h);
	}

	center.x = x + w * scale / 2;
	center.y = y + h * scale / 2;

	t.setSmooth(true);
	ob.setTexture(t);
	ob.setPosition(x, y);
	ob.setScale(scale, scale);
}

Obstacle::Obstacle(const Obstacle &other): x { other.x }, y{ other.y }, speed{ other.speed }, t{ other.t }, 
w{ other.w }, h{ other.h }, aniLength{ other.aniLength }, scale{ other.scale }, r{ other.r } {
	animations = new sf::Vector2i[aniLength];
	for (int i = 0; i < aniLength; i++) {
		animations[i] = other.animations[i];
	}

	center.x = x + w * scale / 2;
	center.y = y + h * scale / 2;

	t.setSmooth(true);
	ob.setTexture(t);
	ob.setPosition(x, y);
	ob.setScale(scale, scale);
}

Obstacle &Obstacle::operator=(Obstacle &&other) {
	std::swap(*this, other);
	return *this;
}

//
bool Obstacle::update() {
	x -= speed;
	center.x = x + w * scale / 2;
	if (x < -w * scale) {
		// returns true when wrapping around
		x = 960 + w * scale;
		return true;
	}
	// otherwise returns false
	return false;
}

void Obstacle::setSpeed(int s) {
	speed = s;
}

// causes obstacle to become something else visually speaking (depends on spritesheet, and 
// need user specification with a Vector2i object, for dim, sheet location, and everything else)
void Obstacle::changeForm(int aL, double scale, int newY, sf::Vector2i boxPos, sf::Vector2i dim) {
	delete[] animations;
	aniLength = aL;
	w = dim.x;
	h = dim.y;
	y = newY;
	frame = 0;

	animations = new sf::Vector2i[aniLength];
	for (int i = 0; i < aniLength; i++) {
		animations[i] = sf::Vector2i(boxPos.x, boxPos.y + i * h);
	}

	center.x = x + w * scale / 2;
	center.y = y + h * scale / 2;
	
	ob.setScale(scale, scale);
	ob.setPosition(x, y);
}

void Obstacle::draw(sf::RenderWindow &window) {
	if (frame == aniLength) {
		frame = 0;
	}
	ob.setTextureRect(sf::IntRect(animations[frame].x, animations[frame].y, w, h));
	if (framecount % 4 == 0) {
		frame++;
	}
	framecount++;
	ob.setPosition(x, y);
	window.draw(ob);
}

// these two just do exactly as they say
sf::Vector2i Obstacle::getCenter() {
	return center;
}

int Obstacle::getRadius() {
	return r;
}

Obstacle::~Obstacle() {
	delete[] animations;
}


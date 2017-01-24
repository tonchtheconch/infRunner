#include "bg.h"

BG::BG(sf::Texture &Layer, int speed, int width, float scale) 
	: Layer{ Layer }, x1 { 0 }, x2{ width }, speed{ speed }, width{ width } {
	img1.setTexture(Layer);
	img1.setScale(scale, scale);
	img1.setPosition(x1, y);
	img2.setTexture(Layer);
	img2.setScale(scale, scale);
	img2.setPosition(x2, y);
}

void BG::draw(sf::RenderWindow &window) {
	img1.setPosition(x1, y);
	img2.setPosition(x2, y);
	window.draw(img1);
	window.draw(img2);
}

void BG::scroll() {
	if (x1 == -width) {
		x1 = width;
	}
	if (x2 == -width) {
		x2 = width;
	}
	x1 -= speed;
	x2 -= speed;
}
#include "runner.h"

Runner::Runner(int x, int y, sf::Texture &t) : x{ x }, y{ y }, t{ t } {
	t.setSmooth(true);
	mc.setTexture(t);
	mc.setPosition(x, y);
	mc.setScale(0.1, 0.1);
	animations[0] = sf::Vector2i(1181, 0);
	animations[1] = sf::Vector2i(2307, 0);
	animations[2] = sf::Vector2i(0, 893);
	animations[3] = sf::Vector2i(1126, 893);
	animations[4] = sf::Vector2i(0, 0);
	animations[5] = sf::Vector2i(2252, 875);
}

Runner::Runner(int x, int y, int r, sf::Texture &t) : x{ x }, y{ y }, t{ t }, r{ r } {
	t.setSmooth(true);
	mc.setTexture(t);
	mc.setPosition(x, y);
	mc.setScale(0.1, 0.1);

	center.x = x + (1181 * 0.1) / 2;
	center.y = y + (892 * 0.1) / 2;

	animations[0] = sf::Vector2i(1181, 0);
	animations[1] = sf::Vector2i(2307, 0);
	animations[2] = sf::Vector2i(0, 893);
	animations[3] = sf::Vector2i(1126, 893);
	animations[4] = sf::Vector2i(0, 0);
	animations[5] = sf::Vector2i(2252, 875);
}

// these two just do exactly as they say
sf::Vector2i Runner::getCenter() {
	return center;
}

int Runner::getRadius() {
	return r;
}

//bounces the runner up will return false when finish jumping
bool Runner::jump() {
	if (timer < 40) {
		timer++;
		y -= 3;
	} else {
		y += 3;
		timer++;
	}

	center.y = y + (892 * 0.1) / 2;

	if (timer == 80) {
		timer = 0;
		return false;
	}
	return true;
}

void Runner::draw(sf::RenderWindow &window) {
	if (notHit) {
		if (frame == 4) {
			frame = 0;
		}
	} else {
		if (frame == 5) {
			frame = 4;
		}
		
	}
	mc.setTextureRect(sf::IntRect(animations[frame].x, animations[frame].y, 1125, 874));
	if (framecount % 4 == 0) {
		frame++;
	}
	framecount++;
	mc.setPosition(x, y);
	window.draw(mc);
}

void Runner::setNotHit(bool hit) {
	notHit = hit;
}
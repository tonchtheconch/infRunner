#include <SFML/Graphics.hpp>
#include "runner.h"
#include "obstacle.h"
#include "bg.h"
#include "enemyFactory.h"

//remember to remove later
#include <iostream>
using namespace std;

int main() {
	int width = 960;
	int height = 540;
	int groundLevel = 455;
	bool hit = false;
	sf::Font f;
	if (!f.loadFromFile("fonts/AdobeFanHeitiStd-Bold.otf")) {
		cerr << "error: missing file" << endl;
	}
	
	int tSize = 144;
	sf::Text GaOv;
	GaOv.setString("Game Over");
	GaOv.setCharacterSize(tSize);
	GaOv.setPosition(sf::Vector2f(width/2 - (5 * tSize) / 2, height/2 - tSize / 2));
	GaOv.setFillColor(sf::Color::Red);
	GaOv.setOutlineColor(sf::Color::Black);
	GaOv.setOutlineThickness(tSize * 0.05);
	GaOv.setFont(f);
	
	//setting up the mc object
	sf::Texture mcT;
	if (!mcT.loadFromFile("characters/MainCharacters/MC.png")) {
		cerr << "error: missing file" << endl;
	}
	Runner mc(200, groundLevel - 87, 40, mcT);
	
	sf::Texture enT;
	if (!enT.loadFromFile("characters/Enemies/FullMap.png")) {
		cerr << "error: missing file" << endl;
	}
	/* Obstacle(int x, int y, int speed, double scale, sf::Texture &t,
		int aniLength, int w, int h, int startx, int starty); */
	
	vector <Enemy> enemies;
	//Large ones
	//diglett
	
	enemies.emplace_back(Enemy{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 505, 611 },
		sf::Vector2i{ 970, groundLevel - 122 }, enT, 0.2, 8, 34 });
	//the blue one
	enemies.emplace_back(Enemy{ sf::Vector2i{ 0, 4888 }, sf::Vector2i{ 582, 691 },
		sf::Vector2i{ 970, groundLevel - 138 }, enT, 0.2, 2, 54 });
	//the flyer
	enemies.emplace_back(Enemy{ sf::Vector2i{ 0, 6272 }, sf::Vector2i{ 712, 520 },
		sf::Vector2i{ 970, groundLevel - 150 }, enT, 0.1, 2, 21 });
	//the spike bro
	enemies.emplace_back(Enemy{ sf::Vector2i{ 0, 7314 }, sf::Vector2i{ 369, 369 },
		sf::Vector2i{ 970, groundLevel - 74 }, enT, 0.2, 2, 37 });
	//the small orange one
	enemies.emplace_back(Enemy{ sf::Vector2i{ 370, 7314 }, sf::Vector2i{ 212, 235 },
		sf::Vector2i{ 970, groundLevel - 94 }, enT, 0.4, 2, 36 });
	
	//for debug should remove eventually
	cout << enemies.size() << endl;

	EnemyFactory eF{ enT, enemies };
	int n = 1;
	sf::Texture backGround;
	sf::Texture clouds;
	sf::Texture midGround;
	sf::Texture trees;
	sf::Texture foreGround;

	if (!backGround.loadFromFile("background/layer_01.png") 
		|| !clouds.loadFromFile("background/layer_02.png")
		|| !midGround.loadFromFile("background/layer_03.png") 
		|| !trees.loadFromFile("background/layer_04.png") 
		|| !foreGround.loadFromFile("background/layer_05.png")) {
		cerr << "error: missing file" << endl;
	}
	BG layer1{ backGround, 1, width, 0.5 };
	BG layer2{ clouds, 2, width, 0.5 };
	BG layer3{ midGround, 3, width, 0.5 };
	BG layer4{ trees, 4, width, 0.5 };
	BG layer5{ foreGround, 5, width, 0.5 };
	
	bool jump = false;

	//create window with exit button and titlebar
	sf::RenderWindow window(sf::VideoMode(width, height), "A free runner ?", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	// game loop
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//wipe the screen
		layer1.draw(window);
		layer2.draw(window);
		layer3.draw(window);
		layer4.draw(window);
		layer5.draw(window);

		mc.draw(window);
		eF.draw(window);

		if (hit) {
			window.draw(GaOv);
		}
		
		window.display();

		//a better proof of concept
		
		if (eF.pubHitTest(mc)) {
			hit = true;
			mc.setNotHit(false);
		} 

		if (!hit) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				jump = true;
			}
			// will jump until mc.jump() return false ie: decides stop
			if (jump) {
				if (!mc.jump()) {
					jump = false;
				}
			}

			eF.update();
			//layer1.scroll();
			layer2.scroll();
			layer3.scroll();
			layer4.scroll();
			layer5.scroll();
		}

	}

	return 0;
}
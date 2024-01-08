#ifndef CBACKGROUND_H
#define CBACKGROUND_H
#include <vector>
#include "CLAYER.h"
#include "SFML/Graphics.hpp"

class CBACKGROUND {
public:
	void init();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);
private:
	std::vector<CLAYER*> background;
};


class CSNOW {
public:
	void init();
	void update(float deltaTime, float mapScrollSpeed);
	void render(sf::RenderWindow* window);
private:
	sf::Sprite snow1;
	sf::Sprite snow2;
};
#endif // !CBACKGROUND_H
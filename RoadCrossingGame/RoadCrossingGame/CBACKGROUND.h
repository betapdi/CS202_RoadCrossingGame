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

#endif // !CBACKGROUND_H
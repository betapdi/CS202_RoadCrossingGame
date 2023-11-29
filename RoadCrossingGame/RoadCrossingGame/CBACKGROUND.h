#ifndef CBACKGROUND_
#define CBACKGROUND_
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

#endif // !CBACKGROUND_
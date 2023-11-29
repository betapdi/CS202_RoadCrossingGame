#ifndef CLAYER_
#define CLAYER_

#include <iostream>
#include <string>
#include <vector>
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "CASSET.h"
#include <iostream>

class CLAYER {
public:
	void init(std::string name, float speed);
	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	void setPosition(sf::Vector2f pos);
private:
	sf::Sprite background1;
	sf::Sprite background2;
	sf::Vector2i sizeOfBG;
	float speed;
};

#endif // !CLAYER_
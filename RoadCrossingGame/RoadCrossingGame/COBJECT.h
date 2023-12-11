#ifndef COBJECT_H
#define COBJECT_H

#include "SFML/Graphics.hpp"
#include "WindowConnector.h"
#include "Constants.h"
#include "CASSET.h"
#include <array>

typedef std::array<bool, Constants::SCREEN_HEIGHT / Constants::ROAD_SIZE> column;

class COBJECT {
public:
	COBJECT(sf::Texture* texture, sf::Vector2f pos);
	
	void createDummyMap(int length);
	void draw(sf::RenderWindow* window);
private:
	std::vector<column> map;
	sf::Sprite sprite;
};

#endif // !COBJECT_H

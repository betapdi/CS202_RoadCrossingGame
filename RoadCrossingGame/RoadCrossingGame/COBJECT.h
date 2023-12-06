#ifndef COBJECT_H
#define COBJECT_H

#include "SFML/Graphics.hpp"
#include "WindowConnector.h"
#include "Constants.h"
#include "CASSET.h"

class COBJECT {
public:
	COBJECT();
	void draw(sf::RenderWindow* window);
	void init();
	void update(float deltaTime);

private:
	sf::Sprite objectSprite;
};

#endif // !COBJECT_H


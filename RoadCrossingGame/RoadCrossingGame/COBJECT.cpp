#include "COBJECT.h"

COBJECT::COBJECT(sf::Texture* texture, sf::Vector2f pos) {
	sprite.setTexture(*texture);
	sprite.setScale(Constants::SCALE_OF_ROAD, Constants::SCALE_OF_ROAD);
	sprite.setPosition(pos);
}

void COBJECT::createDummyMap(int length) {
	for (int i = 0; i < length; i++) {
		column c = column();
		c[c.size() - 1] = true;
		map.push_back(c);
	}
}

void COBJECT::draw(sf::RenderWindow* window) {
	int x = 0;
	for (column& col : map) {
		int y = 0;
		for (bool& draw : col) {
			if (draw) {
				sprite.setPosition(sf::Vector2f(x, y) * (float)Constants::ROAD_SIZE);
				window->draw(sprite);
			}
			y++;
		}
		x++;
	}
}

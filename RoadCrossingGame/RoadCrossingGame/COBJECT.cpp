#include "COBJECT.h"

COBJECT::COBJECT(sf::Texture* texture) {
	sprite.setTexture(*texture);
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
				sprite.setPosition(x * 16, y * 16);
				window->draw(sprite);
			}
			y++;
		}
		x++;
	}
}

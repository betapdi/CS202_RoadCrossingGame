#include "CBACKGROUND.h"

void CBACKGROUND::init() {
	CLAYER* layer;
	for (int i = 0; i < 6; ++i) {
		layer = new CLAYER();
		std::string path = "city/" + std::to_string(i + 1) + ".png";
		switch (i) {
		case 0:
			layer->init(path, 50);
			break;
		case 1:
			layer->init(path, 70);
			break;
		case 2:
			layer->init(path, 85);
			break;
		case 3:
			layer->init(path, 100);
			break;
		case 4:
			layer->init(path, 120);
			break;
		case 5:
			layer->init(path, 175);
			break;
		case 6:
			layer->init(path, 150);
			break;
		}
		background.push_back(layer);
	}
}

void CBACKGROUND::update(float deltaTime) {
	for (auto layer : background) {
		layer->update(deltaTime);
	}
}

void CBACKGROUND::render(sf::RenderWindow* window) {
	for (auto layer : background) {
		layer->render(window);
	}
}

void CSNOW::init() {
	snow1.setTexture(*Constants::SNOW);
	snow2.setTexture(*Constants::SNOW);

	snow2.setPosition(0.0f, 0.0f);
	long yCoor = Constants::SNOW->getSize().y;
	snow1.setPosition(0, -yCoor);
}

void CSNOW::update(float deltaTime, float mapScrollSpeed) {
	snow2.move(0, mapScrollSpeed * deltaTime);
	snow1.move(0, mapScrollSpeed * deltaTime);

	// Reset the snowflakes if they go below the screen
	if (snow1.getPosition().y >= 0) {
		snow2.setPosition(0, 0);
		long yCoor = Constants::SNOW->getSize().y;
		snow1.setPosition(0, -yCoor);
	}
}

void CSNOW::render(sf::RenderWindow* window) {
	window->draw(snow1);
	window->draw(snow2);
}

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

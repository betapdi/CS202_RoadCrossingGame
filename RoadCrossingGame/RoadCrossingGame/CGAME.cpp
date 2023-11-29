#include "CGAME.h"

CGAME::CGAME() {
	this->videoMode.width = Constants::SCREEN_WIDTH;
	this->videoMode.height = Constants::SCREEN_HEIGHT;

	menu = new CMENU;
	gameState = MENU;
}

CGAME::~CGAME() {
	if (window != nullptr) delete window;
	if (menu != nullptr) delete menu;
}

void CGAME::init() {
	this->window = new sf::RenderWindow(this->videoMode, "Crossy Road", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
	curWindow->setWindow(window);
	menu->init();
}

void CGAME::update(float deltaTime) {
	menu->update(deltaTime);
}

void CGAME::render() {
	switch (gameState) {
	case MENU:
		menu->draw(window);
		break;
	case PLAYING:
		break;
	case GAMEOVER:
		break;
	case PAUSE:
		break;
	case SETTING:
		break;
	}
	window->display();
}

void CGAME::run() {
	init();
	float deltaTime;
	while (window->isOpen()) {
		deltaTime = clock.restart().asSeconds();
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					menu->setChoice(menu->moveUp());
					break;
				case sf::Keyboard::Down:
					menu->setChoice(menu->moveDown());
					break;
				default:
					break;
				}
			}
		}
		update(deltaTime);
		render();
	}
}
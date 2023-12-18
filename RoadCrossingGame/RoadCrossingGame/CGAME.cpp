//#include "CGAME.h"
//
//CGAME::CGAME() {
//	this->videoMode.width = Constants::SCREEN_WIDTH;
//	this->videoMode.height = Constants::SCREEN_HEIGHT;
//
//	menu = new CMENU;
//	gameState.push(MENU);
//}
//
//CGAME::~CGAME() {
//	if (window != nullptr) delete window;
//	if (menu != nullptr) delete menu;
//}
//
//void CGAME::init() {
//	this->window = new sf::RenderWindow(this->videoMode, "Crossy Road", sf::Style::Titlebar | sf::Style::Close);
//	this->window->setFramerateLimit(60);
//	this->window->setVerticalSyncEnabled(false);
//	curWindow->setWindow(window);
//	menu->init();
//	menu->drawMenu();
//	//states->addState(new CMENU);
//	//gameState.push(MENU);
//}
//
//void CGAME::update(float deltaTime) {
//	menu->update(deltaTime);
//}
//
//void CGAME::getSelectionFromMenu(int choice) {
//	switch (choice) {
//	case 0:
//		//PLAY
//		gameState.push(MENU);
//		break;
//	case 1:
//		//SETTING
//		gameState.push(SETTING);
//		break;
//	case 2:
//		//LOAD GAME
//		break;
//	case 3:
//		//QUIT GAME
//		this->window->close();
//		break;
//	}
//}
//
//void CGAME::render() {
//	switch (gameState.top()) {
//	case MENU:
//		menu->draw(window, MENU);
//		break;
//	case SETTING:
//		break;
//	case GAMEOVER:
//		break;
//	case PAUSE:
//		break;
//	case SETTING:
//		menu->draw(window, SETTING);
//		break;
//	}
//	window->display();
//}
//
//void CGAME::run() {
//	init();
//	float deltaTime;
//	//while (window->isOpen()) {
//	//	//states->getCurrentState()->init();
//	//	states->getCurrentState()->processInput();
//	//	states->getCurrentState()->update();
//	//	states->getCurrentState()->draw(window);
//	//}
//	while (window->isOpen()) {
//		deltaTime = clock.restart().asSeconds();
//		while (window->pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				window->close();
//			}
//			else if (event.type == sf::Event::KeyReleased) {
//				switch (event.key.code) {
//				case sf::Keyboard::Up:
//					menu->moveUp();
//					//menu->setChoice(menu->moveUp());
//					break;
//				case sf::Keyboard::Down:
//					menu->moveDown();
//					//menu->setChoice(menu->moveDown());
//					break;
//				case sf::Keyboard::Enter:
//					getSelectionFromMenu(menu->getChoice());
//				default:
//					break;
//				}
//			}
//		}
//		update(deltaTime);
//		render();
//	}
//}
#include "CGAME.h"
CGAME::CGAME() {
	this->videoMode.width = Constants::SCREEN_WIDTH;
	this->videoMode.height = Constants::SCREEN_HEIGHT;
	window = new sf::RenderWindow(this->videoMode, "Crossy Road", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
	curWindow->setWindow(window);
}
CGAME::~CGAME() {
	if (window != nullptr) delete window;
}
void CGAME::init() {
	STATEMACHINE::getInstance()->pushState(stateTypes::MENU);
	//STATEMACHINE::getInstance()->changeState(stateTypes::MENU);
	STATEMACHINE::getInstance()->performStateChange();
}
void CGAME::processEvents() {
	if (STATEMACHINE::getInstance()->hasStates()) {
		STATEMACHINE::getInstance()->performStateChange();
	}
	STATEMACHINE::getInstance()->getCurrentState()->processEvents();
}
void CGAME::update(float deltaTime) {
	//if (STATEMACHINE::getInstance()->hasStates()) {
	//	STATEMACHINE::getInstance()->performStateChange();
	//}
	STATEMACHINE::getInstance()->getCurrentState()->update(deltaTime);
}
void CGAME::render() {
	STATEMACHINE::getInstance()->getCurrentState()->render(window);
	window->display();
}
void CGAME::run() {
	init();
	sf::Clock clock;
	float deltaTime = 0.0f;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window->isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();
			update(TIME_PER_FRAME.asSeconds());
		}
		render();
	}
}
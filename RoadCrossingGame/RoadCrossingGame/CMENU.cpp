#include "CMENU.h"
//
//CMENU::CMENU() {
//	choice = 0;
//	prevChoice = -1;
//}
//
//void CMENU::draw(sf::RenderWindow* window, int menuState) {
//	intro.render(window);
//	if (menuState == 0) {
//		window->draw(crossyroad);
//		window->draw(cursor);
//	}
//	else if (menuState == 4) {
//		//Draw setting page
//		drawSetting();
//		for (int i = 0; i < 3; ++i) {
//			window->draw(rrect[i]);
//		}		
//		
//		for (int i = 0; i < 8; ++i) {
//			window->draw(button[i]);
//		}
//	}
//	for (int i = 0; i < Constants::maxMenu; ++i) {
//		window->draw(option[i]);
//	}	
//
//}
//
//void CMENU::init() {
//	intro.init();
//
//	choice = 0;
//	//TITLE: CROSSY ROAD
//	crossyroad.setString("CROSSY ROAD");
//	crossyroad.setFont(*Constants::LUCKIESTGUY);
//	crossyroad.setFillColor(sf::Color(136, 28, 28, 255));
//	crossyroad.setCharacterSize(120);
//	crossyroad.setOutlineThickness(10);
//	crossyroad.setOutlineColor(sf::Color::White);
//	sf::FloatRect textBounds = crossyroad.getGlobalBounds();
//	float centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
//	float centerY = (curWindow->getWindow()->getSize().y - textBounds.height) / 2.0f;
//	crossyroad.setPosition(centerX, centerY - 200);
//
//	//MENU: PLAY, QUIT, SETTING, LOAD GAME
//	option[0].setString("PLAY");
//	option[1].setString("SETTING");
//	option[2].setString("LOAD GAME");
//	option[3].setString("EXIT");
//	centerY = (curWindow->getWindow()->getSize().y - option[0].getGlobalBounds().height) / 2.0f;
//	for (int i = 0; i < Constants::maxMenu; ++i) {
//		option[i].setFont(*Constants::BRUCE_FOREVER);
//		option[i].setFillColor(sf::Color::White);
//		option[i].setCharacterSize(40);
//		sf::FloatRect textBounds = option[i].getGlobalBounds();
//		float centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
//		originalPos[i] = sf::Vector2f(centerX, centerY + i * 65);
//		option[i].setPosition(originalPos[i]);
//	}
//
//	//Cursor at menu
//	cursor.setTexture(*Constants::CURSOR);
//	cursor.setRotation(-22.0f);
//	sf::Vector2u textureSize = Constants::CURSOR->getSize();
//	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
//	cursor.setPosition(option[2].getPosition().x - 60, centerY + 20);
//	updatePosCursor = cursor.getPosition();
//}
//
//void CMENU::processInput() {
//	sf::Event event;
//	while (window->pollEvent(event)) {
//		if (event.type == sf::Event::Closed) {
//			window->close();
//		}
//		else if (event.type == sf::Event::KeyReleased) {
//			switch (event.key.code) {
//			case sf::Keyboard::Up:
//				moveUp();
//				break;
//			case sf::Keyboard::Down:
//				moveDown();
//				break;
//			}
//		}
//	}
//}
//
//void CMENU::draw(sf::RenderWindow* window) {
//	intro.render(window);
//	window->draw(crossyroad);
//	for (int i = 0; i < Constants::maxMenu; ++i) {
//		window->draw(option[i]);
//	}
//	window->draw(cursor);
//	window->display();
//}
//
//void CMENU::drawMenu() {
//	//MENU: PLAY, QUIT, SETTING, LOAD GAME
//	option[0].setString("PLAY");
//	option[1].setString("SETTING");
//	option[2].setString("LOAD GAME");
//	option[3].setString("EXIT");
//	float centerY = (curWindow->getWindow()->getSize().y - option[0].getGlobalBounds().height) / 2.0f;
//	for (int i = 0; i < Constants::maxMenu; ++i) {
//		option[i].setFont(*Constants::BRUCE_FOREVER);
//		option[i].setFillColor(sf::Color::White);
//		option[i].setCharacterSize(40);
//		sf::FloatRect textBounds = option[i].getGlobalBounds();
//		float centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
//		originalPos[i] = sf::Vector2f(centerX, centerY + i * 65);
//		option[i].setPosition(originalPos[i]);
//	}
//
//	//Cursor at menu
//	cursor.setTexture(*Constants::CURSOR);
//	cursor.setRotation(-22.0f);
//	sf::Vector2u textureSize = Constants::CURSOR->getSize();
//	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
//	cursor.setPosition(option[2].getPosition().x - 60, centerY + 20);
//	updatePosCursor = cursor.getPosition();
//}
//
//void CMENU::drawSetting() {
//	for (int i = 0; i < Constants::maxMenu; ++i) {
//		option[i].setString("");
//	}
//
//	rrect[0].setSize(sf::Vector2f(926, 500));
//	rrect[0].setCornersRadius(10);
//	rrect[0].setCornerPointCount(40);
//	rrect[0].setPosition(177, 70);
//	rrect[0].setFillColor(sf::Color(251, 211, 185, 230));	
//	
//	rrect[1].setSize(sf::Vector2f(926, 70));
//	rrect[1].setCornersRadius(10);
//	rrect[1].setCornerPointCount(40);
//	rrect[1].setPosition(177, 600);
//	rrect[1].setFillColor(sf::Color(251, 211, 185, 230));	
//	
//	rrect[2].setSize(sf::Vector2f(387, 62));
//	rrect[2].setCornersRadius(10);
//	rrect[2].setCornerPointCount(40);
//	rrect[2].setPosition(452, 493);
//	rrect[2].setFillColor(sf::Color(119, 52, 59, 255));
//
//
//	button[0].setTexture(*Constants::QUIT);
//	button[1].setTexture(*Constants::MOVE_LEFT);
//	button[2].setTexture(*Constants::MOVE_RIGHT);
//	button[3].setTexture(*Constants::MUSIC_ON);
//	button[4].setTexture(*Constants::MUSIC_OFF);
//	button[5].setTexture(*Constants::SFX_ON);
//	button[6].setTexture(*Constants::SFX_OFF);
//	button[7].setTexture(*Constants::RESET);
//
//	sf::Vector2u textureSize;
//
//	button[0].setRotation(-20.f);
//	button[0].setScale(0.2f, 0.2f);
//	textureSize = Constants::QUIT->getSize();
//	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
//	button[0].setPosition(1215, 20);
//
//	for (int i = 1; i < 8; ++i) {
//		if (i < 3) {
//			button[i].setScale(0.23, 0.23);
//		}
//		else {
//			button[i].setScale(0.28, 0.28);
//		}
//	}
//
//	button[1].setPosition(467, 493);
//	button[2].setPosition(467 + 300, 493);
//	button[3].setPosition(350, 604);
//	//button[4].setPosition(350, 604);
//	button[5].setPosition(350 + 290, 604);
//	//button[6].setPosition(350 + 290, 604);
//	button[7].setPosition(350 + 2 * 290	, 604);
//}
//
//
//void CMENU::update() {
//	if (prevChoice != -1) {
//		option[prevChoice].setPosition(originalPos[prevChoice]);
//		option[prevChoice].setOutlineThickness(0);
//	}
//	option[choice].setOutlineThickness(7);
//	option[choice].setOutlineColor(sf::Color(240, 194, 170, 255));
//}
//
//void CMENU::update(float deltaTime) {
//	intro.update(deltaTime);
//	update();
//	//Floating effect
//	accumulatedTime += deltaTime;
//	if (accumulatedTime > 0.3f) {
//		cursorVisible = !cursorVisible;
//		accumulatedTime = 0.0f;
//	}
//
//	//Blink effect
//	if (cursorVisible) {
//		cursor.setTextureRect(sf::IntRect(0, 0, Constants::CURSOR->getSize().x, Constants::CURSOR->getSize().y));
//	}
//	else {
//		cursor.setTextureRect(sf::IntRect(0, 0, 0, 0));
//	}
//
//	elapsedTime += deltaTime;
//	float floatOffset = floatAmplitude * std::sin(floatFrequency * elapsedTime);
//	option[choice].setPosition(originalPos[choice].x, originalPos[choice].y + floatOffset);
//}
//
//int CMENU::getChoice() {
//	return choice;
//}
//
//void CMENU::setChoice(const int& choice) {
//	this->choice = choice;
//}

CMENU::CMENU() {
	choice = 0;
	prevChoice = -1;
	currentTime = 0;
	isEntered = false;
}
CMENU::~CMENU() {

}
void CMENU::exit() {

}
void CMENU::pause() {

}
void CMENU::resume() {

}
void CMENU::init() {
	intro.init();
	choice = 0;

	GBUTTON* button;

	//Quit
	button = new GBUTTON();
	button->init(Constants::QUIT);
	button->setRotation(-20.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(Constants::SCREEN_WIDTH - 1.5 * button->getSize().x, button->getSize().y / 2);
	button->setClickFunction([]() {
		STATEMACHINE::getInstance()->popState();
		});
	buttonList.push_back(button);

	//TITLE: CROSSY ROAD
	crossyroad.setString("CROSSY ROAD");
	crossyroad.setFont(*Constants::LUCKIESTGUY);
	crossyroad.setFillColor(sf::Color(136, 28, 28, 255));
	crossyroad.setCharacterSize(120);
	crossyroad.setOutlineThickness(10);
	crossyroad.setOutlineColor(sf::Color::White);
	sf::FloatRect textBounds = crossyroad.getGlobalBounds();
	float centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
	float centerY = (curWindow->getWindow()->getSize().y - textBounds.height) / 2.0f;
	crossyroad.setPosition(centerX, centerY - 200);

	//MENU: PLAY, QUIT, SETTING, LOAD GAME
	option[0].setString("PLAY");
	option[1].setString("SETTING");
	option[2].setString("LOAD GAME");
	option[3].setString("CREDITS");
	option[4].setString("RANKING");
	centerY = (curWindow->getWindow()->getSize().y - option[0].getGlobalBounds().height) / 2.0f;
	for (int i = 0; i < Constants::maxMenu; ++i) {
		option[i].setFont(*Constants::BRUCE_FOREVER);
		option[i].setFillColor(sf::Color::White);
		option[i].setCharacterSize(40);
		sf::FloatRect textBounds = option[i].getGlobalBounds();
		float centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
		originalPos[i] = sf::Vector2f(centerX, centerY + i * 65);
		option[i].setPosition(originalPos[i]);
	}

	//Cursor at menu
	cursor.setTexture(*Constants::CURSOR);
	cursor.setRotation(-22.0f);
	sf::Vector2u textureSize = Constants::CURSOR->getSize();
	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
	cursor.setPosition(option[2].getPosition().x - 60, centerY + 20);
	//updatePosCursor = cursor.getPosition();
}
void CMENU::moveUp() {
	prevChoice = choice;
	choice = (--choice + Constants::maxMenu) % Constants::maxMenu;
}

void CMENU::moveDown() {
	prevChoice = choice;
	choice = (++choice) % Constants::maxMenu;
}

//void CMENU::moveCursor(int choice) {
//	cursor.setPosition(originalPos[2].x - 60, originalPos[choice].y + 20);
//}
//
//void CMENU::updateMenu(int choice) {
//	if (prevChoice != -1) {
//		option[prevChoice].setPosition(originalPos[prevChoice]);
//		option[prevChoice].setOutlineThickness(0);
//	}
//	option[choice].setOutlineThickness(7);
//	option[choice].setOutlineColor(sf::Color(240, 194, 170, 255));
//	moveCursor(choice);
//}

void CMENU::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			curWindow->getWindow()->close();
		}
		if (event.type == sf::Event::Resized) {
			sf::View view;
			view.setSize(event.size.width, event.size.height);
			curWindow->getWindow()->setView(view);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isEntered) {
			moveUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isEntered) {
			moveDown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			isEntered = true;
		}
	}
}

void CMENU::update(float deltaTime) {
	intro.update(deltaTime);

	if (prevChoice != -1) {
		option[prevChoice].setPosition(originalPos[prevChoice]);
		option[prevChoice].setOutlineThickness(0);
	}
	option[choice].setOutlineThickness(7);
	option[choice].setOutlineColor(sf::Color(240, 194, 170, 255));
	cursor.setPosition(originalPos[2].x - 60, originalPos[choice].y + 20);

	//Floating effect
	accumulatedTime += deltaTime;
	if (accumulatedTime > 0.3f) {
		cursorVisible = !cursorVisible;
		accumulatedTime = 0.0f;
	}

	//Blink effect
	if (cursorVisible) {
		cursor.setTextureRect(sf::IntRect(0, 0, Constants::CURSOR->getSize().x, Constants::CURSOR->getSize().y));
	}
	else {
		cursor.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}

	elapsedTime += deltaTime;
	float floatOffset = floatAmplitude * std::sin(floatFrequency * elapsedTime);
	option[choice].setPosition(originalPos[choice].x, originalPos[choice].y + floatOffset);

	if (isEntered) {
		if (choice == 0) {
			STATEMACHINE::getInstance()->changeState(stateTypes::PLAYING, 0);
		}
		else if (choice == 1) {
			STATEMACHINE::getInstance()->changeState(stateTypes::SETTING, 0);
		}
		else if (choice == 2) {
			// LOAD GAME
			STATEMACHINE::getInstance()->changeState(stateTypes::PLAYING, 1);
		}
		else if (choice == 3) {
			STATEMACHINE::getInstance()->changeState(stateTypes::CREDIT, 0);
		}
		else if (choice == 4) {
			STATEMACHINE::getInstance()->changeState(stateTypes::RANKING, 0);
		}
		isEntered = !isEntered;
	}
}

void CMENU::render(sf::RenderWindow* window) {
	intro.render(window);
	window->draw(crossyroad);
	for (int i = 0; i < Constants::maxMenu; ++i) {
		window->draw(option[i]);
	}
	window->draw(cursor);
}

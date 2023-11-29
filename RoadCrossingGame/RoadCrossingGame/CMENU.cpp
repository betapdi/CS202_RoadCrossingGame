#include "CMENU.h"

CMENU::CMENU() {
	choice = 0;
	prevChoice = -1;
}

void CMENU::draw(sf::RenderWindow* window) {
	intro.render(window);
	window->draw(crossyroad);
	for (int i = 0; i < Constants::maxMenu; ++i) {
		window->draw(option[i]);
	}
	window->draw(cursor);
}

void CMENU::init() {
	intro.init();
	choice = 0;
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
	option[3].setString("EXIT");
	centerY = (curWindow->getWindow()->getSize().y - option[0].getGlobalBounds().height) / 2.0f;
	for (int i = 0; i < Constants::maxMenu; ++i) {
		option[i].setFont(*Constants::BRUCE_FOREVER);
		option[i].setFillColor(sf::Color::White);
		option[i].setCharacterSize(40);
		textBounds = option[i].getGlobalBounds();
		centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
		originalPos[i] = sf::Vector2f(centerX, centerY + i * 65);
		option[i].setPosition(originalPos[i]);
	}

	//Cursor at menu
	cursor.setTexture(*Constants::CURSOR);
	cursor.setRotation(-22.0f);
	sf::Vector2u textureSize = Constants::CURSOR->getSize();
	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
	cursor.setPosition(option[2].getPosition().x - 60, centerY + 20);
	updatePosCursor = cursor.getPosition();
}

int CMENU::moveUp() {
	prevChoice = choice;
	choice = (--choice + Constants::maxMenu) % Constants::maxMenu;
	moveCursor(choice);
	return choice;
}

int CMENU::moveDown() {
	prevChoice = choice;
	choice = (++choice) % Constants::maxMenu;
	moveCursor(choice);
	return choice;
}

void CMENU::moveCursor(int choice) {
	cursor.setPosition(originalPos[2].x - 60, originalPos[choice].y + 20);
}

void CMENU::update(int choice) {
	if (prevChoice != -1) {
		option[prevChoice].setPosition(originalPos[prevChoice]);
		option[prevChoice].setOutlineThickness(0);
	}
	option[choice].setOutlineThickness(7);
	option[choice].setOutlineColor(sf::Color(240, 194, 170, 255));
}

void CMENU::update(float deltaTime) {
	intro.update(deltaTime);
	update(choice);
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
}

int CMENU::getChoice() {
	return choice;
}

void CMENU::setChoice(const int& choice) {
	this->choice = choice;
}

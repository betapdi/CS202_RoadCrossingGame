#include "GBUTTON.h"

GBUTTON::GBUTTON() {
	isHandling = false;
	clickFunc = nullptr;
	isFocus = 0;
	orgCursor.loadFromSystem(sf::Cursor::Arrow);
}

GBUTTON::~GBUTTON() {
}

void GBUTTON::init(sf::Texture* texture) {
	this->setTexture(texture);
	this->setSize(sf::Vector2f(62, 62));

	float expansionAmount = 30.0f;
	sf::FloatRect expandBound (
		this->getGlobalBounds().left + expansionAmount,
		this->getGlobalBounds().top + expansionAmount,
		this->getGlobalBounds().width + 2 * expansionAmount,
		this->getGlobalBounds().height + 2 * expansionAmount
	);
	//this->getGlobalBounds = expandBound;
}

void GBUTTON::update(float deltaTime) {
	handleTouchEvent();
	if (isFocus) {
		orgCursor.loadFromSystem(sf::Cursor::Hand);
		curWindow->getWindow()->setMouseCursor(orgCursor);
	}
	else {
		orgCursor.loadFromSystem(sf::Cursor::Arrow);
		curWindow->getWindow()->setMouseCursor(orgCursor);
	}
}

void GBUTTON::render(sf::RenderWindow* window) {
	window->draw(*this);
}

void GBUTTON::handleTouchEvent() {
	isHandling = false;
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::MouseMoved) {
			if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				isFocus = true;
			}
			else {
				isFocus = false;
			}
		}
	}

	if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			clickFunc();
			isHandling = true;
		}
	}
}

bool GBUTTON::isPressed() {
	return isHandling;
}

void GBUTTON::setClickFunction(void(*func)()) {
	clickFunc = func;
}

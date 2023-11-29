#include "CLAYER.h"

void CLAYER::init(std::string name, float speed) {
	sf::Texture* texture;
	texture = CASSET::getInstance()->GetTexture(name);
	sizeOfBG = (sf::Vector2i)texture->getSize();

	background1.setTexture(*texture);
	background2.setTexture(*texture);

	background1.setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - sizeOfBG.y / 2));
	background2.setPosition(sizeOfBG.x * 1.5f, background1.getPosition().y);

	background2.setOrigin((sf::Vector2f)sizeOfBG * 0.5f);
	background1.setOrigin((sf::Vector2f)sizeOfBG * 0.5f);

	this->speed = speed;
}

void CLAYER::update(float deltaTime) {
	background1.move(-speed * deltaTime, 0);
	background2.move(-speed * deltaTime, 0);

	if (background2.getPosition().x <= Constants::SCREEN_WIDTH / 2) {
		background1.setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - sizeOfBG.y / 2));
		background2.setPosition(sizeOfBG.x * 1.5f, background1.getPosition().y);
	}
}

void CLAYER::render(sf::RenderWindow* window) {
	window->draw(background1);
	window->draw(background2);
}

void CLAYER::setPosition(sf::Vector2f pos) {
	background1.setPosition((sf::Vector2f)pos);
	background2.setPosition(pos.x + sizeOfBG.x, pos.y);
}

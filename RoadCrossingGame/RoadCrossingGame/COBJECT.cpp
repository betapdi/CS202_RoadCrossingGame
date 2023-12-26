#include "COBJECT.h"
#include "CRESOURCEHOLDER.h"
#include <iostream>

const sf::IntRect COBJECT::getTexture(int type) {
	return sf::IntRect(SIZE * type, 0, SIZE, SIZE);
}

Textures::ID fromIntToType(int type) {
	switch (type) {
	case 0:
		return Textures::TRAFFIC_LIGHT;
		break;
	default:
		return Textures::TRAFFIC_LIGHT;
		break;
	}
}

COBJECT::COBJECT(int type, const TextureHolder& textures, sf::Vector2f position) {
	sprite.setTexture(textures.get(fromIntToType(type)));
	sprite.setPosition(position);
	sprite.setOrigin(SIZE / 2.0f, SIZE);
	//deltaTime = randInt(1, 5);
	deltaTime = rand() % 6 - 1;
	normal();
}

void COBJECT::normal() {
	status = 0;
	sprite.setTextureRect(getTexture(status));
	clock.restart();
}

void COBJECT::turnRed() {
	status = 1;
	sprite.setTextureRect(getTexture(status));
	clock.restart();
}

void COBJECT::turnYellow() {
	status = 2;
	sprite.setTextureRect(getTexture(status));
	clock.restart();
}

void COBJECT::turnGreen() {
	status = 3;
	sprite.setTextureRect(getTexture(status));
	clock.restart();
}

int COBJECT::lightStatus() {
	return status;
}

void COBJECT::updateTrafficLight() {
	switch (status) {
	case 0:
		if (clock.getElapsedTime().asSeconds() >= 3 + deltaTime)
			turnRed();
		break;
	case 1:
		if (clock.getElapsedTime().asSeconds() >= 3 + deltaTime)
			turnGreen();
		break;
	case 2:
		if (clock.getElapsedTime().asSeconds() >= 2 + deltaTime)
			turnRed();
		break;
	case 3:
		if (clock.getElapsedTime().asSeconds() >= 4 + deltaTime)
			turnYellow();
		break;
	default:
		break;
	}
}

void COBJECT::updateCurrent(float deltaTime) {
	updateTrafficLight();
}

void COBJECT::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

sf::FloatRect COBJECT::getRect() {
	sf::FloatRect bounds = sprite.getLocalBounds();
	sf::FloatRect sizeOfObj = { this->getPosition() - sf::Vector2f(SIZE / 2.0f, SIZE), sf::Vector2f(bounds.width, bounds.height) };
	return sizeOfObj;
}

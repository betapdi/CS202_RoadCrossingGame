#include "CMONEY.h"
#include "CRESOURCEHOLDER.h"

Textures::ID getTextureID() {
	return Textures::MONEY;
}

CMONEY::CMONEY(const TextureHolder& textures, float frameTime)
	: mAnimation(textures.get(getTextureID()), sf::Vector2i(14, 1), frameTime)
	, isCollected(false)
	, hasSFX(true)
{
	mAnimation.setScale(2.0f, 2.0f);
	sf::FloatRect getBound = mAnimation.getGlobalBounds();
	bound = { 0, 0, getBound.width, getBound.height};
	box.setSize(sf::Vector2f(getBound.width, getBound.height));
	box.setPosition(getBound.left, getBound.top);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red); // You can set any color you prefer
	box.setOutlineThickness(2.0f);
}

void CMONEY::updateCurrent(float deltaTime) {
	mAnimation.update(deltaTime);
}

void CMONEY::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!isCollected) {
		target.draw(mAnimation, states);
		target.draw(box, states);
	}
	else {
		return;
	}
}

bool CMONEY::isIntersect(const sf::FloatRect& rect) {
	sf::FloatRect getBound = getBorder();
	//return getBound.intersects(rect);
	/*std::cout << getBound.top << "-" << getBound.left << "-" << getBound.width << "-" << getBound.height << std::endl;
	std::cout << rect.top << "-" << rect.left << "-" << rect.width << "-" << rect.height << std::endl;*/
	return getBound.intersects(rect);
}

sf::FloatRect CMONEY::getBorder() {
	return sf::FloatRect(mAnimation.getGlobalBounds().left + pos.x, mAnimation.getGlobalBounds().top + pos.y, bound.width, bound.height);
}

void CMONEY::setCollected(bool isCollected) {
	this->isCollected = isCollected;
}

bool CMONEY::isCollect() {
	return isCollected;
}
void CMONEY::savePos(sf::Vector2f position) {
	pos = position;
}

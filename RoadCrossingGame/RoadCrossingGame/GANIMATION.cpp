#include "GANIMATION.h"

GANIMATION::GANIMATION(sf::Texture texture, sf::Vector2i frameNum, float frameTime) : frameNum(frameNum), frameTime(frameTime) {
	this->setTexture(texture);
	curFrame = sf::Vector2i(0, 0);
	curTime = 0;
	calculateRectSize();
	calculateRectUV();
	applyRect();
}

void GANIMATION::calculateRectSize() {
	rectSize = sf::Vector2i(this->getTexture()->getSize().x / frameNum.x, this->getTexture()->getSize().y / frameNum.y);
}

void GANIMATION::calculateRectUV() {
	rectUV.x = curFrame.x * rectSize.x;
	rectUV.y = curFrame.y * rectSize.y;
}

void GANIMATION::applyRect() {
	rect = sf::IntRect(rectUV, rectSize);
	this->setTextureRect(rect);
}

void GANIMATION::update(float deltaTime) {
	curTime += deltaTime;
	if (curTime >= frameTime) {
		curFrame.x++;
		if (curFrame.x == frameNum.x) {
			curFrame.x = 0;
		}
		calculateRectUV();
		applyRect();
		curTime -= frameTime;
	}
}

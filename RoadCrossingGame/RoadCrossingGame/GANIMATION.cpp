#include "GANIMATION.h"

GANIMATION::GANIMATION()
	: frameNum(0, 0), curFrame(0, 0), frameTime(0), curTime(0), rectUV(0, 0), rectSize(0, 0)
{
}

GANIMATION::GANIMATION(const sf::Texture& texture, sf::Vector2i frameNum, float frameTime) {
	this->frameNum = frameNum;
	this->frameTime = frameTime;
	this->setTexture(texture);
	curTime = 0.0f;
	curFrame.x = 0;
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
	uvRect = sf::IntRect(rectUV, rectSize);
	this->setTextureRect(uvRect);
}

void GANIMATION::update(float deltaTime) {
	curTime += deltaTime;
	if (curTime >= frameTime) {
		curFrame.x++;
		if (curFrame.x == frameNum.x) {
			curFrame.x = 0;
			curFrame.y = (curFrame.y + 1) % frameNum.y;
		}
		calculateRectUV();
		applyRect();
		curTime -= frameTime;
	}
}
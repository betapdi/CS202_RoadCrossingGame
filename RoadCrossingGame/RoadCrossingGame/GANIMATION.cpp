#include "GANIMATION.h"

GANIMATION::GANIMATION(sf::Texture texture, sf::Vector2i frameNum, float frameTime) {
	this->frameNum = frameNum;
	this->frameTime = frameTime;
	this->setTexture(texture);
	curTime = 0.0f;
	curFrame.x = 0;
	uvRect.width = texture.getSize().x / float(frameNum.x);
	uvRect.height = texture.getSize().y / float(frameNum.y);
	//curFrame = sf::Vector2i(0, 0); 
	//curTime = 0;
	//calculateRectSize();
	//calculateRectUV();
	//applyRect();
}

void GANIMATION::update(int row, float deltaTime) {
	curFrame.y = row;
	curTime += deltaTime;
	if (curTime >= frameTime) {
		curTime -= frameTime;
		curFrame.x++;
		if (curFrame.x >= frameNum.x) {
			curFrame.x = 0;
		}
	}

	uvRect.left = curFrame.x * uvRect.width;
	uvRect.top = curFrame.y * uvRect.height;

}

//void GANIMATION::calculateRectSize() {
//	rectSize = sf::Vector2i(this->getTexture()->getSize().x / frameNum.x, this->getTexture()->getSize().y / frameNum.y);
//}
//
//void GANIMATION::calculateRectUV() {
//	rectUV.x = curFrame.x * rectSize.x;
//	rectUV.y = curFrame.y * rectSize.y;
//}
//
//void GANIMATION::applyRect() {
//	rect = sf::IntRect(rectUV, rectSize);
//	this->setTextureRect(rect);
//}
//
//void GANIMATION::update(float deltaTime) {
//	curTime += deltaTime;
//	if (curTime >= frameTime) {
//		curFrame.x++;
//		if (curFrame.x == frameNum.x) {
//			curFrame.x = 0;
//		}
//		calculateRectUV();
//		applyRect();
//		curTime -= frameTime;
//	}
//}
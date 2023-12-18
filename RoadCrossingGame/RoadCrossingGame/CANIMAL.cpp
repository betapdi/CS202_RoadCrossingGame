#include "CANIMAL.h"
#include "CRESOURCEHOLDER.h"
#include "GMAP.h"

Textures::ID toTextureID(CANIMAL::Animal type) {
	switch (type) {
	case CANIMAL::BEAR_RIGHT:
		return Textures::BEAR_RIGHT;
		break;
	case CANIMAL::BEAR_LEFT:
		return Textures::BEAR_LEFT;
		break;
	case CANIMAL::DEER_L:
		return Textures::DEER_L;
		break;
	case CANIMAL::DEER_R:
		return Textures::DEER_R;
		break;
	case CANIMAL::REINDEER_L:
		return Textures::REINDEER_L;
		break;
	case CANIMAL::REINDEER_R:
		return Textures::REINDEER_R;
		break;
	case CANIMAL::FOX_L:
		return Textures::FOX_L;
		break;
	case CANIMAL::FOX_R:
		return Textures::FOX_R;
		break;
	case CANIMAL::WOLF_L:
		return Textures::WOLF_L;
		break;
	case CANIMAL::WOLF_R:
		return Textures::WOLF_R;
		break;
	}
}

CANIMAL::Animal fromIntToType(int type) {
	switch (type) {
	case 0:
		return CANIMAL::BEAR_RIGHT;
		break;
	case 1:
		return CANIMAL::BEAR_LEFT;
		break;
	case 2:
		return CANIMAL::DEER_R;
		break;
	case 3:
		return CANIMAL::DEER_L;
		break;
	case 4:
		return CANIMAL::REINDEER_R;
		break;
	case 5:
		return CANIMAL::REINDEER_L;
		break;
	case 6:
		return CANIMAL::FOX_R;
		break;
	case 7:
		return CANIMAL::FOX_L;
		break;
	case 8:
		return CANIMAL::WOLF_R;
		break;
	case 9:
		return CANIMAL::WOLF_L;
		break;
	}
}

int fromIntToDir(int dir) {
	if (dir % 2 == 0) {
		return 1;
	}
	else return - 1;
}

CANIMAL::CANIMAL(int type, sf::FloatRect mWorldBound, const TextureHolder& textures, float speedMove, float frameTime)
	: mType(fromIntToType(type))
	, mWorldBound(mWorldBound)
	, mSpeed(speedMove)
	, mDirection(fromIntToDir(type))
	, mAnimation(textures.get(toTextureID(mType)), getFrameNum(type), frameTime)
{
	std::cout << "Direction: " << this->mDirection << std::endl;
	mAnimation.setScale(2, 2);
	/*sf::FloatRect bounds = mAnimation.getLocalBounds();
	mAnimation.setOrigin(bounds.width / 2, 0);*/
}

sf::Vector2i CANIMAL::getFrameNum(int type) {
	if (type == 0 || type == 1 || type == 8 || type == 9) {
		return sf::Vector2i(6, 1);
	}
	else return sf::Vector2i(4, 1);
}

void CANIMAL::saveOrgPos(const sf::Vector2f& position) {
	orgPos = position;
}

void CANIMAL::updateCurrent(float deltaTime) {
	mAnimation.update(deltaTime);
	//if (mWorldBound.intersects(mAnimation.getGlobalBounds())) {
	//sf::Vector2f getPos = mAnimation.getPosition();
	//if (getPos.x >= Constants::SCREEN_WIDTH || getPos.x <= 0) {
	//	mAnimation.setPosition(orgPos);
	//}
	mAnimation.move(mDirection * mSpeed * deltaTime, 0);
	//}
}

int CANIMAL::getDirection() {
	return mDirection;
}

void CANIMAL::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mAnimation, states);
}
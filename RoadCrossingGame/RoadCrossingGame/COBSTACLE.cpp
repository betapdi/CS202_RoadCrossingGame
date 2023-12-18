#include "COBSTACLE.h"
#include "CRESOURCEHOLDER.h"
#include <random>

Textures::ID toTextureID(COBSTACLE::obstacleType type) {
	switch (type) {
	case COBSTACLE::SMALL_TREE:
		return Textures::SMALL_TREE;
		break;
	case COBSTACLE::BIG_TREE:
		return Textures::BIG_TREE;
		break;
	case COBSTACLE::BENCH:
		return Textures::BENCH;
		break;
	/*case COBSTACLE::GRASS:
		return Textures::GRASS;
		break;*/
	case COBSTACLE::VENDING_MACHINE:
		return Textures::VENDING_MACHINE;
		break;
	case COBSTACLE::BLUE_SIGN:
		return Textures::BLUE_SIGN;
		break;
	case COBSTACLE::GREEN_SIGN:
		return Textures::GREEN_SIGN;
		break;
	case COBSTACLE::WHITE_SIGN:
		return Textures::WHITE_SIGN;
		break;
	case COBSTACLE::HOTDOG:
		return Textures::HOTDOG;
		break;
	case COBSTACLE::LIGHT:
		return Textures::LIGHT;
		break;
	case COBSTACLE::GROCERY:
		return Textures::GROCERY;
		break;
	case COBSTACLE::SHOP:
		return Textures::SHOP;
		break;
	case COBSTACLE::HOUSE:
		return Textures::HOUSE;
		break;
	}
}

COBSTACLE::obstacleType fromIntToType(int type) {
	switch (type) {
	case 0:
		return COBSTACLE::SMALL_TREE;
		break;
	case 1:
		return COBSTACLE::BIG_TREE;
		break;
	case 2:
		return COBSTACLE::BENCH;
		break;
	/*case 3:
		return COBSTACLE::GRASS;
		break;*/
	case 3:
		return COBSTACLE::VENDING_MACHINE;
		break;
	case 4:
		return COBSTACLE::BLUE_SIGN;
		break;
	case 5:
		return COBSTACLE::GREEN_SIGN;
		break;
	case 6:
		return COBSTACLE::WHITE_SIGN;
		break;
	case 7:
		return COBSTACLE::HOTDOG;
		break;
	case 8:
		return COBSTACLE::LIGHT;
		break;
	case 9:
		return COBSTACLE::GROCERY;
		break;
	case 10:
		return COBSTACLE::SHOP;
		break;
	case 11:
		return COBSTACLE::HOUSE;
		break;
	}
}


COBSTACLE::COBSTACLE(int type, const TextureHolder& textures)
	: mType(fromIntToType(type))
	, mSprite(textures.get(toTextureID(mType)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(0, bounds.height);
	//mSprite.setScale(1.5, 1.5);
}


COBSTACLE::COBSTACLE(obstacleType type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

float COBSTACLE::getWidthObstacle() {
	sf::FloatRect sizeOfObj = mSprite.getLocalBounds();
	return sizeOfObj.width;
}


void COBSTACLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}

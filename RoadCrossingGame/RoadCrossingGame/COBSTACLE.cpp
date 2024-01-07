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
	case COBSTACLE::TRAFFIC_LIGHT:
		return Textures::TRAFFIC_LIGHT;
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
	case 12:
		return COBSTACLE::TRAFFIC_LIGHT;
		break;
	}
}


COBSTACLE::COBSTACLE(const TextureHolder& textures) {
}

COBSTACLE::COBSTACLE(int type, const TextureHolder& textures)
	: type(type)
	,mType(fromIntToType(type))
	, mSprite(textures.get(toTextureID(mType)))
{
	bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(0, bounds.height);
	//mSprite.setScale(1.5, 1.5);
}


//COBSTACLE::COBSTACLE(obstacleType type, const TextureHolder& textures)
//	: mType(type)
//	, mSprite(textures.get(toTextureID(type)))
//{
//	bounds = mSprite.getLocalBounds();
//	mSprite.setOrigin(0, bounds.height);
//}


sf::FloatRect COBSTACLE::getRect() {
	//sf::FloatRect bounds = mSprite.getLocalBounds();
	//if (this != nullptr) {
	//	sf::FloatRect sizeOfObj = { pos.x, pos.y - 60.0f, bounds.width, 60.0f };
	//	return sizeOfObj;
	//}
	//return { 0,0,0,0 };
	//return { pos.x, pos.y, bounds.width, 60.0f };
	sf::FloatRect bounds = mSprite.getLocalBounds();
	sf::Vector2f getPos = this->getPosition();
	sf::FloatRect sizeOfObj = { getPos.x, getPos.y - bounds.height - 20, bounds.width, bounds.height };
	return sizeOfObj;
}

float COBSTACLE::getSizeX() const {
	//if (this != nullptr) {
		sf::FloatRect bound = mSprite.getGlobalBounds();
		return bound.width;
	//}
	//return 0;
}

void COBSTACLE::savePos(const sf::Vector2f& pos) {
	this->pos = pos;
}

void COBSTACLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}

void COBSTACLE::save(std::ofstream& fout) const {
	fout.write((char*)(&type), sizeof(int));
	fout.write((char*)(&pos), sizeof(sf::Vector2f));
}

//void COBSTACLE::load(std::ifstream& fin) {
//	fin.read((char*)(&type), sizeof(int));
//	fin.read((char*)(&pos), sizeof(sf::Vector2f));
//}
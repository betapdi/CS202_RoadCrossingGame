#include "COBSTACLE.h"
#include "CRESOURCEHOLDER.h"
#include <random>

Textures::ID toTextureID(COBSTACLE::obstacleType type) {
	switch (type) {
	case COBSTACLE::FAST_FOOD_STORE:
		return Textures::FAST_FOOD_STORE;
		break;
	case COBSTACLE::COFFEE_SHOP:
		return Textures::COFFEE_SHOP;
		break;
	case COBSTACLE::GROCERY:
		return Textures::GROCERY;
		break;
	case COBSTACLE::SHOP:
		return Textures::SHOP;
		break;
	case COBSTACLE::BARBER_SHOP:
		return Textures::BARBER_SHOP;
		break;
	case COBSTACLE::BREAD_SHOP:
		return Textures::BREAD_SHOP;
		break;	
	case COBSTACLE::VEGETABLE_SHOP:
		return Textures::VEGETABLE_SHOP;
		break;	
	case COBSTACLE::HOUSE:
		return Textures::HOUSE;
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
	case COBSTACLE::VENDING_MACHINE:
		return Textures::VENDING_MACHINE;
		break;	
	case COBSTACLE::GRASS:
		return Textures::GRASS;
		break;
	}
}

COBSTACLE::obstacleType fromIntToType(int type) {
	switch (type) {
	case 0:
		return COBSTACLE::FAST_FOOD_STORE;
		break;
	case 1:
		return COBSTACLE::COFFEE_SHOP;
		break;
	case 2:
		return COBSTACLE::GROCERY;
		break;
	case 3:
		return COBSTACLE::SHOP;
		break;
	case 4:
		return COBSTACLE::BARBER_SHOP;
		break;
	case 5:
		return COBSTACLE::BREAD_SHOP;
		break;
	case 6:
		return COBSTACLE::VEGETABLE_SHOP;
		break;
	case 7:
		return COBSTACLE::HOUSE;
		break;
	case 8:
		return COBSTACLE::BLUE_SIGN;
		break;
	case 9:
		return COBSTACLE::GREEN_SIGN;
		break;
	case 10:
		return COBSTACLE::WHITE_SIGN;
		break;
	case 11:
		return COBSTACLE::VENDING_MACHINE;
		break;	
	case 12:
		return COBSTACLE::GRASS;
		break;
	}
}

//Textures::ID fromIntToTextureID(int type) {
//	switch (type) {
//	case COBSTACLE::BLUE_BUILDING:
//		return Textures::BLUE_BUILDING;
//		break;
//	case COBSTACLE::RED_BUILDING:
//		return Textures::RED_BUILDING;
//		break;
//	case COBSTACLE::GLASS_BUILDING:
//		return Textures::GLASS_BUILDING;
//		break;
//	case COBSTACLE::GLASS_BUILDING_1:
//		return Textures::GLASS_BUILDING_1;
//		break;
//	case COBSTACLE::COMPLEX_BUILDING:
//		return Textures::COMPLEX_BUILDING;
//		break;
//	case COBSTACLE::GROCERY:
//		return Textures::GROCERY;
//		break;
//	case COBSTACLE::SHOP:
//		return Textures::SHOP;
//		break;
//	case COBSTACLE::SHOP_1:
//		return Textures::SHOP_1;
//		break;
//	case COBSTACLE::BREAD_SHOP:
//		return Textures::BREAD_SHOP;
//		break;
//	}
//}

//COBSTACLE::COBSTACLE(const TextureHolder& textures) {
//	//
//}

COBSTACLE::COBSTACLE(int type, const TextureHolder& textures)
	: mType(fromIntToType(type))
	, mSprite(textures.get(toTextureID(mType)))
{
	//sf::FloatRect bounds = mSprite.getLocalBounds();
	//mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	//mSprite.setScale(1.5, 1.5);
}


COBSTACLE::COBSTACLE(obstacleType type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void COBSTACLE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}

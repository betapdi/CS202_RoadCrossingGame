#ifndef COBSTACLE_H
#define COBSTACLE_H

#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"

class COBSTACLE : public CSCENENODE {
public:
	enum obstacleType {
		FAST_FOOD_STORE,
		COFFEE_SHOP,
		GROCERY,
		SHOP,
		BARBER_SHOP,
		BREAD_SHOP,
		VEGETABLE_SHOP,
		HOUSE,
		BLUE_SIGN,
		GREEN_SIGN,
		WHITE_SIGN,
		VENDING_MACHINE,
		GRASS,
	};

public:
	//COBSTACLE(const TextureHolder& textures);
	COBSTACLE(int type, const TextureHolder& textures);
	COBSTACLE(obstacleType type, const TextureHolder& textures);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	obstacleType mType;
	sf::Sprite mSprite;
};

#endif // !COBSTACLE_H
#ifndef COBSTACLE_H
#define COBSTACLE_H

#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"

class COBSTACLE : public CSCENENODE {
public:
	enum obstacleType {
		SMALL_TREE,
		BIG_TREE,
		BENCH,
		VENDING_MACHINE,
		BLUE_SIGN,
		GREEN_SIGN,
		WHITE_SIGN,
		HOTDOG,
		LIGHT,
		GROCERY,
		SHOP,
		HOUSE,
	};

public:
	//COBSTACLE(const TextureHolder& textures);
	COBSTACLE(int type, const TextureHolder& textures);
	COBSTACLE(obstacleType type, const TextureHolder& textures);
	float getWidthObstacle();
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	obstacleType mType;
	sf::Sprite mSprite;
};

#endif // !COBSTACLE_H
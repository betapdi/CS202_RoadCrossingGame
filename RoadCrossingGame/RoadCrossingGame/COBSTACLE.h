#ifndef COBSTACLE_H
#define COBSTACLE_H

#include "RESOURCEIDENTIFIER.h"
#include "GANIMATION.h"
#include "CENTITY.h"
#include <fstream>

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
		TRAFFIC_LIGHT,
	};

public:
	COBSTACLE(const TextureHolder& textures);
	COBSTACLE(int type, const TextureHolder& textures);
	//COBSTACLE(obstacleType type, const TextureHolder& textures);
	sf::FloatRect getRect();
	float getSizeX() const;
	void savePos(const sf::Vector2f& pos);
	void save(std::ofstream& file) const;
	void load(std::ifstream& file);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	int type;
	obstacleType mType;
	sf::Sprite mSprite;
	sf::FloatRect bounds;
	sf::Vector2f pos;
};

#endif // !COBSTACLE_H
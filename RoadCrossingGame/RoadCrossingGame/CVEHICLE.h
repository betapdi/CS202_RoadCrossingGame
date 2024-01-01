#ifndef CVEHICLE_H
#define CVEHICLE_H
#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"
#include "GANIMATION.h"
#include "Constants.h"
#include <SFML/Graphics/Sprite.hpp>
/*class CVEHICLE : public CENTITY {
public:
	enum Vehicle {
		TRAIN_LEFT,
		TRAIN_RIGHT,
	};
public:
	CVEHICLE();
	void updateCurrent(float deltaTime);
private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Vehicle mType;
	GANIMATION mAnimation;
	sf::Vector2f orgPos;
	sf::FloatRect mWorldBound;
	float mSpeed;
	float mDirection;
};*/

/*class CVEHICLE : public CENTITY {
public:
	enum Vehicle {
		BLUE_CAR_L,
		BLUE_CAR_R,
		GREEN_CAR_L,
		GREEN_CAR_R,
		//ORANGE_CAR_L,
		//ORANGE_CAR_R,
		RED_CAR_L,
		RED_CAR_R,
		POLICE_CAR_L,
		POLICE_CAR_R,
		BLUE_TRUCK_L,
		BLUE_TRUCK_R,
		TRUCK_L,
		TRUCK_R,
		BUS_L,
		BUS_R,
	};
public:
	CVEHICLE(int type, const TextureHolder& textures, sf::Vector2f position, float speedMove);
	//sf::Vector2i getFrameNum(int type);
	//void saveOrgPos(const sf::Vector2f& position);
	void updateCurrent(float deltaTime);
	void updateVehicle();
	int getDirection();
	int fromIntToDir(int dir);
	sf::FloatRect getBound() const;
private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Vehicle mType;
	//GANIMATION mAnimation;
	sf::Texture mTexture;
	sf::Sprite sprite;
	sf::Vector2f orgPos;
	sf::FloatRect mWorldBound;
	float mSpeed;
	float mDirection;
	float spawnerTime;
	float spawnTimeMax;
	float deltaTime;
	float speedMove;
	//void initSprite(sf::Vector2f position);
};*/

class CVEHICLE : public CENTITY {
public:
	enum Vehicle {
		BLUE_CAR_L,
		BLUE_CAR_R,
		GREEN_CAR_L,
		GREEN_CAR_R,
		//ORANGE_CAR_L,
		//ORANGE_CAR_R,
		RED_CAR_L,
		RED_CAR_R,
		POLICE_CAR_L,
		POLICE_CAR_R,
		BLUE_TRUCK_L,
		BLUE_TRUCK_R,
		TRUCK_L,
		TRUCK_R,
		OLD_TRAIN_L,
		OLD_TRAIN_R,
		TRAIN_L,
		TRAIN_R,
	};
public:
	CVEHICLE(int type, sf::FloatRect mWorldBound, const TextureHolder& textures, float speedMove, float frameTime);
	sf::Vector2i getFrameNum(int type);
	void saveOrgPos(const sf::Vector2f& position);
	virtual void updateCurrent(float deltaTime);
	int getDirection();
	bool isIntersect(const sf::FloatRect& rect);
	sf::FloatRect getBorder();
	int fromIntToDir(int dir);
	sf::FloatRect getBound() const;
private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Vehicle mType;
	GANIMATION mAnimation;
	sf::Vector2f orgPos;
	sf::FloatRect mWorldBound;
	int mDirection;
	float mSpeed;
};
#endif // !CVEHICLE_H
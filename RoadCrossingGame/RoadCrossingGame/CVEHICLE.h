#ifndef CVEHICLE_H
#define CVEHICLE_H
#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"
#include "GANIMATION.h"
#include "Constants.h"
#include <SFML/Graphics/Sprite.hpp>
class CVEHICLE : public CENTITY {
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
};
#endif // !CVEHICLE_H
#ifndef CANIMAL_H
#define CANIMAL_H
#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"
#include "GANIMATION.h"
#include "Constants.h"
#include <SFML/Graphics/Sprite.hpp>
class CANIMAL : public CENTITY {
public:
	enum Animal {
		BEAR_RIGHT,
		BEAR_LEFT,
		DEER_L,
		DEER_R,
		REINDEER_L,
		REINDEER_R,
		FOX_L,
		FOX_R,
		WOLF_L,
		WOLF_R,
	};
public:
	CANIMAL(int type, sf::FloatRect mWorldBound, const TextureHolder& textures, float speedMove, float frameTime);
	sf::Vector2i getFrameNum(int type);
	void saveOrgPos(const sf::Vector2f& position);
	void updateCurrent(float deltaTime);
	int getDirection();
private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Animal mType;
	GANIMATION mAnimation;
	sf::Vector2f orgPos;
	sf::FloatRect mWorldBound;
	int mDirection;
	float mSpeed;
};
#endif // !CANIMAL_H
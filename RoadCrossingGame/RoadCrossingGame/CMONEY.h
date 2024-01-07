#ifndef  CMONEY_H
#define CMONEY_H

#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"
#include "GANIMATION.h"
#include "Constants.h"
#include <SFML/Graphics/Sprite.hpp>

class CMONEY : public CENTITY {
public:
	bool isCollect();
	CMONEY(const TextureHolder& textures, float frameTime);
	bool isIntersect(const sf::FloatRect& rect);
	sf::FloatRect getBorder();
	void setCollected(bool isCollected);
	void savePos(sf::Vector2f position);
	//void drawBounds(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	virtual void updateCurrent(float deltaTime);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	GANIMATION mAnimation;
	sf::FloatRect bound;
	bool isCollected;
	sf::RectangleShape box;
	sf::Vector2f pos;
};

#endif // ! CMONEY_H

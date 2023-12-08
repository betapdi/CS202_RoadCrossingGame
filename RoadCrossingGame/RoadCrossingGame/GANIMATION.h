#ifndef GANIMATION_H
#define GANIMATION_H
#include "SFML/Graphics.hpp"

class GANIMATION : public sf::Sprite{
public:
	GANIMATION(sf::Texture texture, sf::Vector2i frameNum, float frameTime);
	void calculateRectSize();
	void calculateRectUV();
	void applyRect();
	void update(float deltaTime);

private:
	sf::Vector2i frameNum;
	sf::Vector2i curFrame;

	float frameTime;
	float curTime;

	sf::Vector2i rectUV;
	sf::Vector2i rectSize;
	sf::IntRect rect;
};

#endif // !GANIMATION_H
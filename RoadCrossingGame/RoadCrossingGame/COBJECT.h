#ifndef COBJECT_H
#define COBJECT_H

#include "GANIMATION.h"
#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"

class COBJECT : public CENTITY {
public:
	enum Type {
		INVALID,
		RED_LIGHT,
		GREEN_LIGHT,
		YELLOW_LIGHT,
	};
public:
	COBJECT(int type, const TextureHolder& textures, sf::Vector2f position);
	void normal();
	void turnRed();
	void turnGreen();
	void turnYellow();
	int lightStatus();
	void updateCurrent(float deltaTime);
	void updateTrafficLight();
	int getStatus();
	sf::Vector2f getPosition();
	sf::FloatRect getRect();
private:
	const sf::IntRect getTexture(int type);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	const int SIZE = 96;
	sf::Sprite sprite;
	sf::Clock clock;
	float deltaTime;
	int status;
};

#endif // !COBJECT_H


#ifndef CENTITY_H
#define CENTITY_H
#include "CSCENENODE.h"

class CENTITY : public CSCENENODE {
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	void setInitialPosition(sf::Vector2f pos);
	sf::Vector2f getVelocity() const;
private:
	virtual void updateCurrent(float deltaTime);
private:
	sf::Vector2f mVelocity;
	sf::Vector2f mPosition;
};

#endif // !CENTITY_H
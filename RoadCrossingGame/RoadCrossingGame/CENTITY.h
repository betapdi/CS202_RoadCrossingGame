#ifndef CENTITY_H
#define CENTITY_H
#include "CSCENENODE.h"

class CENTITY : public CSCENENODE {
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
private:
	virtual void updateCurrent(float deltaTime);
private:
	sf::Vector2f mVelocity;
};

#endif // !CENTITY_H
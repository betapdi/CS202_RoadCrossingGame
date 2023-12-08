#ifndef GSTATE_H
#define GSTATE_H

#include "SFML/Graphics.hpp"
#include "STATEMACHINE.h"

extern stateTypes;

class GSTATE {
public:
	GSTATE() {}
	virtual ~GSTATE() {}

	virtual void exit() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void init() = 0;
	virtual void processEvents() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow* window) = 0;

	static GSTATE* createGState(stateTypes state);
};

#endif // !GSTATE_H
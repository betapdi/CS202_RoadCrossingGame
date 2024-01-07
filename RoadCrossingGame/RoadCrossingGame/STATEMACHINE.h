#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "SFML/Graphics.hpp"
#include "CSingleton.h"
#include <list>

class GSTATE;

enum stateTypes {
	INVALID = 0,
	MENU,
	SETTING,
	CREDIT,
	RANKING,
	PLAYING,
	GAMEOVER,
	PAUSE,
};

class STATEMACHINE : public CSingleton<STATEMACHINE>{
public:
	STATEMACHINE();
	~STATEMACHINE();

	void changeState(GSTATE* state);
	void changeState(stateTypes state, int type);
	void pushState(stateTypes state);
	void popState();
	void quit();
	void performStateChange();

	bool hasStates();
	GSTATE* getCurrentState() const;
	GSTATE* getNextState() const;	
private:
	std::list<GSTATE*> states;
	GSTATE* activeState;
	GSTATE* nextState;
};

#endif // !STATEMACHINE_H
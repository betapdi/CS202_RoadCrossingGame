#include "STATEMACHINE.h"
#include "GSTATE.h"
#include <iostream>

STATEMACHINE::STATEMACHINE() {
	activeState = nullptr;
	nextState = nullptr;
}

STATEMACHINE::~STATEMACHINE() {
	while (!states.empty()) {
		delete states.back();
		states.pop_back();
	}
}

void STATEMACHINE::changeState(GSTATE* state) {
	nextState = state;
}

void STATEMACHINE::changeState(stateTypes state) {
	GSTATE* gstate = GSTATE::createGState(state);
	if (state == 1) std::cout << "State is MENU.\n";
	else if (state == 2) std::cout << "State is SETTING.\n";
	changeState(gstate);
}

void STATEMACHINE::pushState(stateTypes state) {
	GSTATE* gstate = GSTATE::createGState(state);
	if (!states.empty()) {
		states.back()->pause();
	}
	nextState = gstate;
}

void STATEMACHINE::popState() {
	if (!states.empty()) {
		states.back()->exit();
		states.pop_back();
	}
	if (!states.empty()) {
		states.back()->resume();
	}
	activeState = states.back();
}

void STATEMACHINE::quit(){
	//
}

void STATEMACHINE::performStateChange() {
	if (nextState != nullptr) {
		if (!states.empty()) {
			states.back()->exit();
		}
		states.push_back(nextState);
		states.back()->init();
		activeState = nextState;
	}
	nextState = nullptr;
}

bool STATEMACHINE::hasStates() {
	return states.size() > 0;
}

GSTATE* STATEMACHINE::getCurrentState() const
{
	// TODO: insert return statement here
	return activeState;
}

GSTATE* STATEMACHINE::getNextState() const
{
	// TODO: insert return statement here
	return nextState;
}

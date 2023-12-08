#ifndef CGAME_H
#define CGAME_H
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "CASSET.h"
#include "CSingleton.h"
#include "CBACKGROUND.h"
#include "CMENU.h"
#include <stack>
#include "STATEMACHINE.h"
#include "GSTATE.h"

//enum StateType {
//	MENU,
//	PLAYING,
//	GAMEOVER,
//	PAUSE,
//	SETTING
//};

//class CGAME {
//public:
//	CGAME();
//	~CGAME();
//
//	void init();
//	void update(float deltaTime);
//	void getSelectionFromMenu(int choice);
//	void render();
//	void run();
//private:
//	//Window
//	STATEMACHINE* states;
//	sf::RenderWindow* window;
//	sf::Event event;
//	sf::VideoMode videoMode;
//
//	std::stack<StateType> gameState;
//
//	sf::Clock clock;
//
//	CBACKGROUND intro;
//	CMENU* menu;
//};

class CGAME {
public:
	CGAME();
	~CGAME();

	void run();
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	void init();
	void processEvents();
	void update(float deltaTime);
	void render();
};

#endif // !CGAME_H


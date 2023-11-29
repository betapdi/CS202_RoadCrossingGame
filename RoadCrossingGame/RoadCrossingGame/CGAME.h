#ifndef CGAME_H
#define CGAME_H
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "CASSET.h"
#include "CSingleton.h"
#include "CBACKGROUND.h"
#include "CMENU.h"


enum StateType {
	MENU,
	PLAYING,
	GAMEOVER,
	PAUSE,
	SETTING
};

class CGAME {
public:
	CGAME();
	~CGAME();

	void init();
	void update(float deltaTime);
	void render();
	void run();
private:
	//Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;

	StateType gameState;

	sf::Clock clock;

	CBACKGROUND intro;
	CMENU* menu;
};

#endif // !CGAME_H


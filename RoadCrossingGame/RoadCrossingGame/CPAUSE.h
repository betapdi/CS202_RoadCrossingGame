#ifndef CPAUSE_H
#define CPAUSE_H

#include "SFML/Graphics.hpp"
#include "GSTATE.h"
#include "CASSET.h"
#include "CBACKGROUND.h"
#include "WindowConnector.h"
#include "Constants.h"
#include "CSHAPE.h"
#include "GBUTTON.h"

const int maxPauseOpt = 3;
class CPAUSE : public GSTATE {
public:
	CPAUSE();
	~CPAUSE();

	void exit();
	void pause();
	void resume();

	void init();
	void processEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void moveUp();
	void moveDown();
	void countDown(float elapsedTime);
private:
	CBACKGROUND background;
	sf::Clock clock;
	std::vector<GBUTTON*> buttonList;
	sf::Text option[maxPauseOpt];
	sf::Sprite cursor;
	sf::Vector2f originalPos[maxPauseOpt];
	sf::Text countdown;
	int cntValue;
	bool displayMenu;
	bool displayCountdown;
	int prevChoice;
	int choice;
	bool isEntered = false;
	float currentTime;
	float accumulatedTime = 0.0f;
	bool cursorVisible = true;
	float elapsedTime = 0.0f;
	float floatAmplitude = 9.0f;
	float floatFrequency = 6.5f;
};
#endif // !CPAUSE_H
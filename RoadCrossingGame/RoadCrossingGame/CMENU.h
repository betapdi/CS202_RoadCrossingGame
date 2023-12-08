#ifndef CMENU_H
#define CMENU_H

#include "SFML/Graphics.hpp"
#include "GSTATE.h"
#include "CASSET.h"
#include "CBACKGROUND.h"
#include "WindowConnector.h"
#include "Constants.h"
#include "CSHAPE.h"

class CMENU : public GSTATE{
public:
	CMENU();

	virtual ~CMENU();

	void exit();
	void pause();
	void resume();

	void init();
	void processEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void moveUp();
	void moveDown();
	//void updateMenu(int choice);
	//void draw(sf::RenderWindow* window);

	//void draw(sf::RenderWindow* window, int menuState);
	//void drawMenu();
	//void drawSetting();
	//void moveCursor(int choice);
	////void update(int choice);
	//void update(float deltaTime);
	//int getChoice();
	//void setChoice(const int& choice);
private:
	CBACKGROUND intro;
	int prevChoice;
	int choice;

	sf::Sprite cursor;
	sf::Text crossyroad;
	sf::Text option[Constants::maxMenu];
	sf::Vector2f originalPos[4];
	bool isEntered = false;
	float currentTime;

	//For blink and float effect
	float accumulatedTime = 0.0f;
	bool cursorVisible = true;
	float elapsedTime = 0.0f;
	float floatAmplitude = 9.0f;
	float floatFrequency = 6.5f;
};

#endif // !CMENU_H
#ifndef CMENU_H
#define CMENU_H

#include "SFML/Graphics.hpp"
#include "CASSET.h"
#include "CBACKGROUND.h"
#include "WindowConnector.h"
#include "Constants.h"

class CMENU {
public:
	CMENU();
	void draw(sf::RenderWindow* window);
	void init();
	int moveUp();
	int moveDown();
	void moveCursor(int choice);
	void update(int choice);
	void update(float deltaTime);
	int getChoice();
	void setChoice(const int& choice);
private:
	CBACKGROUND intro;
	int prevChoice;
	int choice;

	sf::Sprite cursor;
	sf::Text crossyroad;
	sf::Text option[Constants::maxMenu];
	//bool isSelected[Constants::maxMenu];
	sf::Vector2f originalPos[4];

	//For blink and float effect
	sf::Vector2f updatePosCursor;
	float accumulatedTime = 0.0f;
	bool cursorVisible = true;
	float elapsedTime = 0.0f;
	float floatAmplitude = 9.0f;
	float floatFrequency = 6.5f;
};

#endif // !CMENU_H
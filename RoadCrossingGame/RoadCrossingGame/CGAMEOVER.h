#ifndef CGAMEOVER_H
#define CGAMEOVER_H
#include "SFML/Graphics.hpp"
#include "GSTATE.h"
#include "CASSET.h"
#include "CBACKGROUND.h"
#include "WindowConnector.h"
#include "Constants.h"
#include "CSHAPE.h"
#include "GBUTTON.h"
const int maxOpt = 4;
class CGAMEOVER : public GSTATE {
public:
	CGAMEOVER();
	~CGAMEOVER();

	void exit();
	void pause();
	void resume();

	void init();
	void processEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void moveUp();
	void moveDown();
private:
	CBACKGROUND intro;
	std::vector<GBUTTON*> buttonList;
	sf::Text gameover;
	sf::Text option[maxOpt];
	sf::Text text[2];
	sf::Text score[2];
	sf::RoundedRectangleShape rrect[2];
	sf::Vector2f originalPos[maxOpt];
	sf::Sprite medal;
	sf::Sprite star;
	sf::Sprite cursor;
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
#endif // !CGAMEOVER_H
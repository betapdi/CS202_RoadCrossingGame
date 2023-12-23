#ifndef CSETTING_H
#define CSETTING_H

#include "SFML/Graphics.hpp"
#include "SFML/Window/Cursor.hpp"
#include "Constants.h"
#include "CBACKGROUND.h"
#include "CSHAPE.h"
#include "GSTATE.h"
#include "GBUTTON.h"
#include "GANIMATION.h"
#include "RESOURCEIDENTIFIER.h"
#include <list>
#include <algorithm>

class CSETTING : public GSTATE {
public:
	CSETTING();
	~CSETTING();

	void exit();
	void pause();
	void resume();

	void init();
	void processEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	//void moveCharacter(int dir, float deltaTime);
private:
	CBACKGROUND background;
	sf::Clock clock;
	std::vector<GBUTTON*> buttonList;
	std::vector<sf::Sprite*> characters;
	std::vector<GANIMATION*> mCharacters;
	sf::RoundedRectangleShape rrect[3];
	sf::Text text[4];
	sf::Cursor cursor;

	bool isInit;
	int cur;
	int curChoice;
	int prevChoice;
	int chooseID;
	int direction;
	GANIMATION* selectedCharacter;
	GANIMATION* prevCharacter;
	sf::Sprite selectedStamp;
	//bool changeCharacter;
	//bool fromLeft;
	//bool fromRight;
	//float moveSpeed;
	//float characterScale;
	//float erasedScale;
	
	bool musicPressed;
	bool sfxPressed;
	bool resetPressed;

	bool isFocus;
	bool isSelected;
	bool chooseFocus;
	bool chooseSelected;
};

#endif // !CSETTING_H
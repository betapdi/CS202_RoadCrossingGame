#ifndef CCREDIT_H
#define CCREDIT_H

#include "SFML/Graphics.hpp"
#include "SFML/Window/Cursor.hpp"
#include "Constants.h"
#include "CBACKGROUND.h"
#include "CSHAPE.h"
#include "GSTATE.h"
#include "GBUTTON.h"
#include <list>
#include <algorithm>
#include "fstream"

const int maxLines = 5;

class CCREDIT : public GSTATE {
public:
	CCREDIT();
	~CCREDIT();

	void exit();
	void pause();
	void resume();

	void init();
	void processEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void readFromFile(const std::string& filename);
private:
	CBACKGROUND background;
	std::vector<GBUTTON*> buttonList;
	sf::RoundedRectangleShape rrect;
	sf::Text text[maxLines];
	sf::Cursor cursor;
};
#endif // !CCREDIT_H
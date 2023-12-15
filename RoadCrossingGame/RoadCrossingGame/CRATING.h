#ifndef CRATING_H
#define CRATING_H

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
#include "Constants.h"

const int maxRank = 3;
class CRATING : public GSTATE {
public:
	CRATING();
	~CRATING();

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
	sf::RoundedRectangleShape table;
	sf::RoundedRectangleShape rrect[maxRank];
	sf::Text text[maxRank];

	sf::Sprite ranking_star;
	sf::Sprite rankNum[3];
	sf::Sprite medal;
};
#endif // !CRATING_H
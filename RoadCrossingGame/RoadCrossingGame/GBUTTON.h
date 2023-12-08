#ifndef GBUTTON_H
#define GBUTTON_H
#include "SFML/Graphics.hpp"
#include "WindowConnector.h"

class GBUTTON : public sf::RectangleShape {
public:
	GBUTTON();
	~GBUTTON();

	void init(sf::Texture* texture);
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void handleTouchEvent();
	bool isPressed();

	void setClickFunction(void (*func)());
private:
	void (*clickFunc)();
	bool isHandling;
	bool isFocus;
	sf::Cursor orgCursor;
	sf::FloatRect expandBound;
};

#endif // !GBUTTON_H
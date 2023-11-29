#ifndef WINDOWCONNECTOR_H
#define WINDOWCONNECTOR_H
#include "CSingleton.h"
#include "SFML/Graphics.hpp"

#define curWindow WindowConnector::getInstance()

class WindowConnector : public CSingleton<WindowConnector> {
public:
	WindowConnector() {
		window = nullptr;
	}

	void setWindow(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* getWindow() {
		return window;
	}
private:
	sf::RenderWindow* window;
};

#endif // !WINDOWCONNECTOR_H
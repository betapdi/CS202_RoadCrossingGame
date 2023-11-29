#ifndef CONSTANT_H
#define CONSTANT_H
#include "CASSET.h"
#include "WindowConnector.h"
#include "SFML/Graphics.hpp"

namespace Constants {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int maxMenu = 4;

	static sf::Font* LUCKIESTGUY = CASSET::getInstance()->GetFont("LuckiestGuy-Regular.ttf");
	static sf::Font* BRUCE_FOREVER= CASSET::getInstance()->GetFont("BruceForeverRegular.ttf");
	static sf::Texture* CURSOR = CASSET::getInstance()->GetTexture("cursor.png");

	static sf::RenderWindow* getCurWindow = WindowConnector::getInstance()->getWindow();
}
#endif // !CONSTANT_H

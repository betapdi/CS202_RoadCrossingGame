#ifndef CONSTANT_H
#define CONSTANT_H
#include "CASSET.h"
#include "WindowConnector.h"
#include "SFML/Graphics.hpp"

namespace Constants {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int maxMenu = 4;
	const int maxCharacters = 5;

	static sf::Font* LUCKIESTGUY	=		CASSET::getInstance()->GetFont("LuckiestGuy-Regular.ttf");
	static sf::Font* BRUCE_FOREVER	=		CASSET::getInstance()->GetFont("BruceForeverRegular.ttf");
	static sf::Texture* CURSOR		=		CASSET::getInstance()->GetTexture("gui/cursor.png");

	static sf::Texture* MUSIC_ON	=		CASSET::getInstance()->GetTexture("gui/music_on.png");
	static sf::Texture* MUSIC_OFF	=		CASSET::getInstance()->GetTexture("gui/music_off.png");
	static sf::Texture* SFX_ON		=		CASSET::getInstance()->GetTexture("gui/sfx_on.png");
	static sf::Texture* SFX_OFF		=		CASSET::getInstance()->GetTexture("gui/sfx_off.png");
	static sf::Texture* MOVE_LEFT	=		CASSET::getInstance()->GetTexture("gui/move_left.png");
	static sf::Texture* MOVE_RIGHT	=		CASSET::getInstance()->GetTexture("gui/move_right.png");
	static sf::Texture* RESET		=		CASSET::getInstance()->GetTexture("gui/back.png");
	static sf::Texture* QUIT		=		CASSET::getInstance()->GetTexture("gui/quit.png");

	static sf::Texture* CLOWN		=		CASSET::getInstance()->GetTexture("character/clown.png");
	static sf::Texture* PENGUIN		=		CASSET::getInstance()->GetTexture("character/penguin.png");
	static sf::Texture* CHICKEN		=		CASSET::getInstance()->GetTexture("character/chicken.png");
	static sf::Texture* DUCK		=		CASSET::getInstance()->GetTexture("character/duck.png");
	static sf::Texture* SQUIRREL		=		CASSET::getInstance()->GetTexture("character/squirrel.png");

	static sf::RenderWindow* getCurWindow = WindowConnector::getInstance()->getWindow();
}
#endif // !CONSTANT_H

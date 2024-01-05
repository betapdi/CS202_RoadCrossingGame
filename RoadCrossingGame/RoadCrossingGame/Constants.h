#ifndef CONSTANT_H
#define CONSTANT_H
#include "CASSET.h"
#include "WindowConnector.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

namespace Constants {
	const int SCREEN_WIDTH			= 1280;
	const int SCREEN_HEIGHT			= 720;
	const int SCALE_OF_ROAD			= 4;
	const int ROAD_SIZE				= 60;

	const int maxMenu				= 5;
	const int maxCharacters			= 5;
	const int maxCar				= 7;
	const int maxObstacle			= 10;
	const int maxAnimal				= 15;

	const enum Layer
	{
		Background,
		Road,
		Animal,
		Obstacle,
		Money,
		Air,
		LayerCount
	};

	static sf::Font* LUCKIESTGUY	=		CASSET::getInstance()->GetFont("LuckiestGuy-Regular.ttf");
	static sf::Font* BRUCE_FOREVER	=		CASSET::getInstance()->GetFont("BruceForeverRegular.ttf");
	static sf::Font* INCONSOLATA	=		CASSET::getInstance()->GetFont("Inconsolata-ExtraBold.ttf");

	static sf::Texture* CURSOR		=		CASSET::getInstance()->GetTexture("gui/cursor.png");

	static sf::Texture* MUSIC_ON	=		CASSET::getInstance()->GetTexture("gui/music_on.png");
	static sf::Texture* MUSIC_OFF	=		CASSET::getInstance()->GetTexture("gui/music_off.png");
	static sf::Texture* SFX_ON		=		CASSET::getInstance()->GetTexture("gui/sfx_on.png");
	static sf::Texture* SFX_OFF		=		CASSET::getInstance()->GetTexture("gui/sfx_off.png");
	static sf::Texture* MOVE_LEFT	=		CASSET::getInstance()->GetTexture("gui/move_left.png");
	static sf::Texture* MOVE_RIGHT	=		CASSET::getInstance()->GetTexture("gui/move_right.png");
	static sf::Texture* RESET		=		CASSET::getInstance()->GetTexture("gui/back.png");
	static sf::Texture* QUIT		=		CASSET::getInstance()->GetTexture("gui/quit.png");
	static sf::Texture* MEDAL		=		CASSET::getInstance()->GetTexture("gui/medal.png");
	static sf::Texture* RANK1		=		CASSET::getInstance()->GetTexture("gui/rank1.png");
	static sf::Texture* RANK2		=		CASSET::getInstance()->GetTexture("gui/rank2.png");
	static sf::Texture* RANK3		=		CASSET::getInstance()->GetTexture("gui/rank3.png");
	static sf::Texture* RANK_STAR	=		CASSET::getInstance()->GetTexture("gui/ranking_star.png");
	static sf::Texture* STAR		=		CASSET::getInstance()->GetTexture("gui/star.png");
	static sf::Texture* STAMP		=		CASSET::getInstance()->GetTexture("gui/selected_stamp.png");


	//static sf::Texture* CLOWN		=		CASSET::getInstance()->GetTexture("character/clown.png");
	//static sf::Texture* PENGUIN		=		CASSET::getInstance()->GetTexture("character/penguin.png");
	//static sf::Texture* CHICKEN		=		CASSET::getInstance()->GetTexture("character/chicken.png");
	//static sf::Texture* DUCK		=		CASSET::getInstance()->GetTexture("character/duck.png");
	//static sf::Texture* SQUIRREL	=		CASSET::getInstance()->GetTexture("character/squirrel.png");
	static sf::Texture* BUNNY		=		CASSET::getInstance()->GetTexture("character/bunny.png");
	static sf::Texture* CAT			=		CASSET::getInstance()->GetTexture("character/cat.png");
	static sf::Texture* PANDA		=		CASSET::getInstance()->GetTexture("character/panda.png");
	static sf::Texture* PANDA1		=		CASSET::getInstance()->GetTexture("character/panda1.png");
	static sf::Texture* PANDA2		=		CASSET::getInstance()->GetTexture("character/panda2.png");

	const enum Characters
	{
		Bunny,
		Cat,
		Panda,
		Panda1,
		Panda2
	};

	static sf::Texture* START_LANE	=		CASSET::getInstance()->GetTexture("objects/statics/start_lane.png");
	static sf::Texture* TOP_LANE	=		CASSET::getInstance()->GetTexture("objects/statics/top_lane1.png");
	static sf::Texture* INNER_LANE	=		CASSET::getInstance()->GetTexture("objects/statics/inner_lane.png");

	static sf::Music* ROUND_N_ROUND = CASSET::getInstance()->GetMusic("roundnround.wav");
	static sf::Sound* MOVE_SFX		= CASSET::getInstance()->GetSound("player_move.wav");
	static sf::Sound* GAME_OVER_SFX = CASSET::getInstance()->GetSound("game_over.wav");
	static sf::Sound* COUNTDOWN_SFX = CASSET::getInstance()->GetSound("countdown_voice.wav");
	static sf::Sound* MONEY_COLLECTED = CASSET::getInstance()->GetSound("money_collected.wav");
	//static sf::RenderWindow* getCurWindow = WindowConnector::getInstance()->getWindow();
}
#endif // !CONSTANT_H

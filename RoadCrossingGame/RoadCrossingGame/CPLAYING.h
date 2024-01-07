#ifndef CPLAYING_H
#define CPLAYING_H
#include "GSTATE.h"
#include "GWORLD.h"
#include "CSHAPE.h"

class CPLAYING : public GSTATE{
public:
	CPLAYING(sf::RenderWindow* window, int type);
	~CPLAYING();

	void exit();
	void pause();
	void resume();

	void init();
	void processEvents();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void updateStatistics(float elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void saveWorld();
	void loadWorld();
private:
	static const sf::Time	TimePerFrame;

	//sf::RenderWindow		mWindow;
	GWORLD						mWorld;
	sf::RoundedRectangleShape	rrect;
	sf::Text					point;
	sf::Font					mFont;
	sf::Text					mStatisticsText;
	float						mStatisticsUpdateTime;
	std::size_t					mStatisticsNumFrames;
	bool isPause;
};

#endif // !CPLAYING_H


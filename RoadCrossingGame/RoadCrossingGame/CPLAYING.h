#ifndef CPLAYING_H
#define CPLAYING_H
#include "GSTATE.h"
#include "GWORLD.h"

class CPLAYING : public GSTATE{
public:
	CPLAYING(sf::RenderWindow* window);
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
private:
	static const sf::Time	TimePerFrame;

	//sf::RenderWindow		mWindow;
	GWORLD					mWorld;

	sf::Font				mFont;
	sf::Text				mStatisticsText;
	float					mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
};

#endif // !CPLAYING_H


#include "CPLAYING.h"
#include "WindowConnector.h"


CPLAYING::CPLAYING(sf::RenderWindow* window)
	: mWorld(*window)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	curWindow->setWindow(window);
	//mFont.loadFromFile("Assets/Font/LuckiestGuy-Regular.ttf");
	//mStatisticsText.setFont(mFont);
	//mStatisticsText.setPosition(5.f, 5.f);
	//mStatisticsText.setCharacterSize(10);
	isPause = false;
}

CPLAYING::~CPLAYING()
{
}

void CPLAYING::exit()
{
}

void CPLAYING::pause()
{
}

void CPLAYING::resume()
{
}

void CPLAYING::init()
{
	player.ini();
}

void CPLAYING::processEvents() {
	player.process();
}

void CPLAYING::update(float deltaTime) {
	if (isPause) {
		STATEMACHINE::getInstance()->changeState(stateTypes::GAMEOVER);
		isPause = !isPause;
	}
	mWorld.update(deltaTime);
}


void CPLAYING::render(sf::RenderWindow* window) {
	window->clear(sf::Color::White);
	mWorld.draw();	
	//sf::View Camera;
	player.render(window);

	window->setView(window->getDefaultView());
	//window->draw(mStatisticsText);

}

void CPLAYING::updateStatistics(float elapsedTime) {
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= 1.0f)
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= 1.0f;
		mStatisticsNumFrames = 0;
	}
}

void CPLAYING::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	//
}

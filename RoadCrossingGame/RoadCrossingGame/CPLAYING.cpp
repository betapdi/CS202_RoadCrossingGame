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

void CPLAYING::init() {
	rrect.setSize(sf::Vector2f(228, 60));
	rrect.setCornersRadius(30);
	rrect.setCornerPointCount(50);
	sf::FloatRect bound = rrect.getGlobalBounds();
	rrect.setOrigin(bound.width / 2, bound.height / 2);
	rrect.setPosition(Constants::SCREEN_WIDTH - bound.width / 1.8f, bound.height / 1.5f);
	rrect.setFillColor(sf::Color(217, 217, 217, 200));

	player.ini();
}

void CPLAYING::processEvents() {
	player.process();
}

void CPLAYING::update(float deltaTime) {
	player.Mouvment(deltaTime);
	if (isPause) {
		STATEMACHINE::getInstance()->changeState(stateTypes::GAMEOVER);
		isPause = !isPause;
	}
	mWorld.update(deltaTime);
}


void CPLAYING::render(sf::RenderWindow* window) {
	sf::View Camera;
	Camera = window->getDefaultView();
	window->setView(player.followView(Camera));
	window->clear(sf::Color::White);
	mWorld.draw();	
	player.render(window);
	
	
//	window->draw(mStatisticsText);

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

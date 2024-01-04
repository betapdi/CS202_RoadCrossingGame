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
}

void CPLAYING::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			/*if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) || !sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
				!sf::Keyboard::isKeyPressed(sf::Keyboard::S) || !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				isPause = true;
			}*/
			if (event.key.code == sf::Keyboard::Escape) STATEMACHINE::getInstance()->changeState(stateTypes::PAUSE);
			else {
				mWorld.setMoveWorld(true);
				mWorld.processEvents(event);
			}
			//handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			mWorld.processEvents(event);
			//handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			curWindow->getWindow()->close();
			break;
		}
	}
}

void CPLAYING::update(float deltaTime) {
	mWorld.update(deltaTime);
}


void CPLAYING::render(sf::RenderWindow* window) {
	window->clear(sf::Color::White);
	mWorld.draw();
	window->draw(point);
	window->setView(window->getDefaultView());
	window->draw(rrect);

	/*sf::View Camera;
	Camera = window->getDefaultView();
	window->setView(player.followView(Camera));*/
	
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

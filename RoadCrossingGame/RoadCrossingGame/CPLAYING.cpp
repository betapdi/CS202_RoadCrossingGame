#include "CPLAYING.h"
#include "WindowConnector.h"


CPLAYING::CPLAYING(sf::RenderWindow* window, int type)
	: mWorld(*window)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	curWindow->setWindow(window);
	std::cout << type << std::endl;
	if (type == 1) loadWorld();
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
	point.setString("0");
	point.setFont(*Constants::LUCKIESTGUY);
	point.setFillColor(sf::Color(254, 185, 44, 255));
	point.setCharacterSize(30);
	point.setOutlineThickness(2);
	point.setOutlineColor(sf::Color::White);
	point.setOrigin(bound.width / 2, bound.height / 2);
	point.setPosition(rrect.getPosition().x +114 , rrect.getPosition().y + 10 );
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
			if (event.key.code == sf::Keyboard::Escape) {
				mWorld.setBackFromPause(true);
				saveWorld();
				STATEMACHINE::getInstance()->changeState(stateTypes::PAUSE, 0);
			}
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
	point.setString(std::to_string(mWorld.score));
}


void CPLAYING::render(sf::RenderWindow* window) {
	mWorld.draw();

	window->setView(window->getDefaultView());
	window->draw(rrect);
	window->draw(point);

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

void CPLAYING::saveWorld() {
	std::ofstream fout;
	fout.open("../Data/Save.dat", std::ios::binary | std::ios::trunc);

	if (fout.is_open()) {
		fout.write((char*)(&mWorld), sizeof(GWORLD));
	}

	else {
		std::cout << "WTF, why can't open???" << std::endl;
	}

	fout.close();
}

void CPLAYING::loadWorld() {
	std::ifstream fin;
	fin.open("../Data/Save.dat");

	if (fin.is_open()) {
		fin.read((char*)(&mWorld), sizeof(GWORLD));
	}

	else {
		std::cout << "WTF, why can't open???" << std::endl;
	}

	fin.close();
}

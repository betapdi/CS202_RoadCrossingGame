#include "CRATING.h"

CRATING::CRATING(){
}

CRATING::~CRATING(){
}

void CRATING::exit(){
}

void CRATING::pause(){
}

void CRATING::resume(){
}

void CRATING::init(){
	background.init();

	GBUTTON* button;

	//Quit
	button = new GBUTTON();
	button->init(Constants::QUIT);
	button->setRotation(-20.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(Constants::SCREEN_WIDTH - 1.5 * button->getSize().x, button->getSize().y / 2);
	button->setClickFunction([]() {
		STATEMACHINE::getInstance()->popState();
		});
	buttonList.push_back(button);

	//Ranking table
	table.setSize(sf::Vector2f(800, 500));
	table.setCornersRadius(10);
	table.setCornerPointCount(40);
	sf::FloatRect bound = table.getGlobalBounds();
	table.setOrigin(bound.width / 2, bound.height / 2);
	table.setOutlineThickness(10);
	table.setOutlineColor(sf::Color(240, 194, 170, 255));
	table.setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2);
	table.setFillColor(sf::Color(119, 52, 59, 255));

	ranking_star.setTexture(*Constants::RANK_STAR);
	bound = ranking_star.getGlobalBounds();
	ranking_star.setOrigin(bound.width / 2, bound.height / 2);
	ranking_star.setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 6);

	rankNum[0].setTexture(*Constants::RANK1);
	rankNum[1].setTexture(*Constants::RANK2);
	rankNum[2].setTexture(*Constants::RANK3);
	for (int i = 0; i < maxRank; ++i) {
		bound = rankNum[i].getGlobalBounds();
		rankNum[i].setOrigin(bound.width / 2, bound.height / 2);
		rankNum[i].setPosition(Constants::SCREEN_WIDTH / 3.6f, Constants::SCREEN_HEIGHT / 2.45f + 95 * i);
	}

	for (int i = 0; i < maxRank; ++i) {
		rrect[i].setSize(sf::Vector2f(438, 65));
		rrect[i].setCornersRadius(30);
		rrect[i].setCornerPointCount(50);
		bound = rrect[i].getGlobalBounds();
		rrect[i].setOrigin(bound.width / 2, bound.height / 2);
		rrect[i].setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2.45f + 95 * i);
		rrect[i].setFillColor(sf::Color(251, 211, 185, 255));
	}

	medal.setTexture(*Constants::MEDAL);
	medal.setPosition(Constants::SCREEN_WIDTH / 2.95f, Constants::SCREEN_HEIGHT / 2.79f);

	std:: ifstream fin;
	fin.open("../Data/Ranking.txt");
	std::string score;

	for (int i = 0; i < maxRank; ++i) {
		fin >> score;
		text[i].setString(score);
		text[i].setFont(*Constants::LUCKIESTGUY);
		text[i].setFillColor(sf::Color(254, 185, 44, 255));
		text[i].setCharacterSize(60);
		text[i].setOutlineThickness(4);
		text[i].setOutlineColor(sf::Color::White);
		bound = text[i].getGlobalBounds();
		text[i].setOrigin(bound.width / 2, bound.height / 2);
		text[i].setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2.55f + 95 * i);
	}

	fin.close();
}

void CRATING::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			curWindow->getWindow()->close();
		}
	}
}

void CRATING::update(float deltaTime) {
	background.update(deltaTime);
	for (auto button : buttonList) {
		button->update(deltaTime);
	}
}

void CRATING::render(sf::RenderWindow* window) {
	background.render(window);
	for (auto button : buttonList) {
		button->render(window);
	}
	window->draw(table);
	window->draw(ranking_star);
	for (int i = 0; i < maxRank; ++i) {
		window->draw(rrect[i]);
		window->draw(rankNum[i]);
		window->draw(text[i]);
	}
	window->draw(medal);
}

void CRATING::readFromFile(const std::string& filename) {
}

#include "CGAMEOVER.h"
#include<fstream>
#include<vector>
CGAMEOVER::CGAMEOVER() {
	choice = 0;
	prevChoice = -1;
	currentTime = 0;
	isEntered = false;
}

CGAMEOVER::~CGAMEOVER()
{
}

void CGAMEOVER::exit()
{
}

void CGAMEOVER::pause()
{
}

void CGAMEOVER::resume()
{
}

void CGAMEOVER::init() {
	intro.init();
	choice = 0;

	GBUTTON* button;

	button = new GBUTTON();
	button->init(Constants::QUIT);
	button->setRotation(-20.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(Constants::SCREEN_WIDTH - 1.5 * button->getSize().x, button->getSize().y / 2);
	button->setClickFunction([]() {
		STATEMACHINE::getInstance()->popState();
		STATEMACHINE::getInstance()->changeState(stateTypes::PLAYING, 0);
	});
	buttonList.push_back(button);

	//TITLE: CROSSY ROAD
	gameover.setString("GAME OVER!");
	gameover.setFont(*Constants::LUCKIESTGUY);
	gameover.setFillColor(sf::Color(136, 28, 28, 255));
	gameover.setCharacterSize(120);
	gameover.setOutlineThickness(10);
	gameover.setOutlineColor(sf::Color::White);
	sf::FloatRect textBounds = gameover.getGlobalBounds();
	float centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
	float centerY = (curWindow->getWindow()->getSize().y - textBounds.height) / 2.0f;
	gameover.setPosition(centerX, centerY - 270);

	option[0].setString("RESTART");
	option[1].setString("MENU");
	option[2].setString("SETTING");
	option[3].setString("RANKING");

	for (int i = 0; i < maxOpt; ++i) {
		option[i].setFont(*Constants::BRUCE_FOREVER);
		option[i].setFillColor(sf::Color::White);
		option[i].setCharacterSize(40);
		sf::FloatRect textBounds = option[i].getGlobalBounds();
		centerX = (curWindow->getWindow()->getSize().x - textBounds.width) / 2.0f;
		originalPos[i] = sf::Vector2f(centerX, centerY + Constants::SCREEN_HEIGHT / 4 + i * 60);
		option[i].setPosition(originalPos[i]);
	}

	cursor.setTexture(*Constants::CURSOR);
	cursor.setRotation(-22.0f);
	sf::Vector2u textureSize = Constants::CURSOR->getSize();
	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
	cursor.setPosition(option[0].getPosition().x - 60, centerY + 20);

	sf::FloatRect bound;
	text[0].setString("YOUR SCORE:");
	text[1].setString("HIGHEST SCORE:");

	std::ifstream fin;
	fin.open("../Data/Ranking.txt");
	std::vector<int>Score;
	while (!fin.eof()) {
		int a;
		fin >> a;
		Score.push_back(a);
	}
	fin.close();

	std::string curScore = std::to_string(Score.back());
	sort(Score.begin(), Score.end()-1, std::greater<int>());
	score[0].setString(curScore);
	score[1].setString(std::to_string(Score[0]));

	std::ofstream fout;
	fout.open("../Data/Ranking.txt");
	for (int i = 0; i < 3; i++)
		fout << Score[i] << "\n";
	fout.close();

	for (int i = 0; i < 2; ++i) {
		//Box
		rrect[i].setSize(sf::Vector2f(400, 80));
		rrect[i].setCornersRadius(10);
		rrect[i].setCornerPointCount(40);
		rrect[i].setOutlineThickness(3);
		rrect[i].setOutlineColor(sf::Color::White);
		rrect[i].setFillColor(sf::Color(119, 52, 59, 255));
		bound = rrect[i].getGlobalBounds();
		rrect[i].setOrigin(bound.width / 2, bound.height / 2);
		rrect[i].setPosition(Constants::SCREEN_WIDTH / 1.5f, Constants::SCREEN_HEIGHT / 2.9f + i * 120);

		//Text
		//text[i].setString(mWorld->getScore());
		text[i].setFont(*Constants::BRUCE_FOREVER);
		text[i].setFillColor(sf::Color::White);
		text[i].setCharacterSize(30);
		text[i].setOutlineThickness(3);
		text[i].setOutlineColor(sf::Color(136, 28, 28, 255));
		textBounds = text[i].getGlobalBounds();
		text[i].setOrigin(0, textBounds.height / 2);
		text[i].setPosition(Constants::SCREEN_WIDTH / 5.2f, Constants::SCREEN_HEIGHT / 2.9f + i * 120);
		
		//Score
		score[i].setFont(*Constants::BRUCE_FOREVER);
		score[i].setFillColor(sf::Color::White);
		score[i].setCharacterSize(50);
		score[i].setOutlineThickness(3);
		score[i].setOutlineColor(sf::Color(136, 28, 28, 255));
		textBounds = score[i].getGlobalBounds();
		score[i].setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
		score[i].setPosition(Constants::SCREEN_WIDTH / 1.5f , Constants::SCREEN_HEIGHT / 3.1f + i * 120);
	}

	star.setTexture(*Constants::STAR);
	bound = star.getGlobalBounds();
	star.setOrigin(bound.width / 2, bound.height / 2);
	star.setPosition(Constants::SCREEN_WIDTH / 1.85f, Constants::SCREEN_HEIGHT / 2.95f);
	
	medal.setTexture(*Constants::MEDAL);
	bound = medal.getGlobalBounds();
	medal.setOrigin(bound.width / 2, bound.height / 2);
	medal.setPosition(Constants::SCREEN_WIDTH / 1.85f, Constants::SCREEN_HEIGHT / 2.96f + 120);
}

void CGAMEOVER::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			curWindow->getWindow()->close();
		}
		if (event.type == sf::Event::Resized) {
			sf::View view;
			view.setSize(event.size.width, event.size.height);
			curWindow->getWindow()->setView(view);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isEntered) {
			moveUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isEntered) {
			moveDown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			isEntered = true;
		}
	}
}

void CGAMEOVER::update(float deltaTime) {
	intro.update(deltaTime);

	if (prevChoice != -1) {
		option[prevChoice].setPosition(originalPos[prevChoice]);
		option[prevChoice].setOutlineThickness(0);
	}
	option[choice].setOutlineThickness(7);
	option[choice].setOutlineColor(sf::Color(240, 194, 170, 255));
	cursor.setPosition(originalPos[0].x - 60, originalPos[choice].y + 20);

	//Floating effect
	accumulatedTime += deltaTime;
	if (accumulatedTime > 0.3f) {
		cursorVisible = !cursorVisible;
		accumulatedTime = 0.0f;
	}

	//Blink effect
	if (cursorVisible) {
		cursor.setTextureRect(sf::IntRect(0, 0, Constants::CURSOR->getSize().x, Constants::CURSOR->getSize().y));
	}
	else {
		cursor.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}

	elapsedTime += deltaTime;
	float floatOffset = floatAmplitude * std::sin(floatFrequency * elapsedTime);
	option[choice].setPosition(originalPos[choice].x, originalPos[choice].y + floatOffset);

	if (isEntered) {
		if (choice == 0) {
			STATEMACHINE::getInstance()->popState();
			STATEMACHINE::getInstance()->changeState(stateTypes::PLAYING, 0);
		}
		else if (choice == 1) {
			STATEMACHINE::getInstance()->popState();
			STATEMACHINE::getInstance()->changeState(stateTypes::MENU, 0);
		}
		else if (choice == 2) {
			STATEMACHINE::getInstance()->changeState(stateTypes::SETTING, 0);
		}
		else if (choice == 3) {
			STATEMACHINE::getInstance()->changeState(stateTypes::RANKING, 0);
		}
		isEntered = !isEntered;
	}
}

void CGAMEOVER::render(sf::RenderWindow* window) {
	intro.render(window);
	window->draw(gameover);
	for (int i = 0; i < 2; ++i) {
		window->draw(rrect[i]);
		window->draw(score[i]);
		window->draw(text[i]);
	}
	window->draw(star);
	window->draw(medal);
	for (int i = 0; i < maxOpt; ++i) {
		window->draw(option[i]);
	}
	window->draw(cursor);
}

void CGAMEOVER::moveUp() {
	prevChoice = choice;
	choice = (--choice + maxOpt) % maxOpt;
}

void CGAMEOVER::moveDown() {
	prevChoice = choice;
	choice = (++choice) % maxOpt;
}

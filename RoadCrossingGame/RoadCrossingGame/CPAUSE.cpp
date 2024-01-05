#include "CPAUSE.h"

CPAUSE::CPAUSE() {
	choice = 0;
	prevChoice = -1;
	currentTime = 0;
	isEntered = false;
	cntValue = 4;
	displayMenu = true;
	displayCountdown = false;
}

CPAUSE::~CPAUSE()
{
}

void CPAUSE::exit()
{
}

void CPAUSE::pause()
{
}

void CPAUSE::resume()
{
}

void CPAUSE::init() {
	background.init();

	option[0].setString("CONTINUE");
	option[1].setString("SAVE GAME");
	option[2].setString("SETTING");

	float centerX = Constants::SCREEN_WIDTH / 2.f;
	float centerY = Constants::SCREEN_HEIGHT / 2.f - 50;
	for (int i = 0; i < maxPauseOpt; ++i) {
		option[i].setFont(*Constants::BRUCE_FOREVER);
		option[i].setFillColor(sf::Color::White);
		option[i].setCharacterSize(40);
		sf::FloatRect textBounds = option[i].getGlobalBounds();
		option[i].setOrigin(textBounds.width / 2, textBounds.height / 2);
		originalPos[i] = sf::Vector2f(centerX, centerY + i * 60);
		option[i].setPosition(originalPos[i]);
	}

	cursor.setTexture(*Constants::CURSOR);
	cursor.setRotation(-22.0f);
	sf::Vector2u textureSize = Constants::CURSOR->getSize();
	cursor.setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
	cursor.setPosition(option[1].getPosition().x - 250, centerY + 20);

	countdown.setFont(*Constants::LUCKIESTGUY);
	countdown.setString("3");
	countdown.setCharacterSize(150);
	countdown.setFillColor(sf::Color(254, 185, 44, 255));
	countdown.setOutlineThickness(4);
	countdown.setOutlineColor(sf::Color::White);
	sf::FloatRect bounds = countdown.getGlobalBounds();
	countdown.setOrigin(bounds.width / 2, bounds.height / 2);
	countdown.setPosition(Constants::SCREEN_WIDTH / 2.f, Constants::SCREEN_HEIGHT / 2.f - 50.0f);
}

void CPAUSE::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			curWindow->getWindow()->close();
		}

		if (event.type == sf::Event::KeyReleased && !displayMenu && cntValue > 0) {
			displayCountdown = true;
		}
		else if (cntValue == 0) {
			displayCountdown = false;
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

void CPAUSE::update(float deltaTime) {
	background.update(deltaTime);

	if (prevChoice != -1) {
		option[prevChoice].setPosition(originalPos[prevChoice]);
		option[prevChoice].setOutlineThickness(0);
	}
	option[choice].setOutlineThickness(7);
	option[choice].setOutlineColor(sf::Color(240, 194, 170, 255));
	cursor.setPosition(originalPos[1].x - 250, originalPos[choice].y + 20);

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

	//count down
	if (!displayMenu) {
		displayCountdown = true;
		countDown(clock.getElapsedTime().asSeconds());
	}

	if (isEntered) {
		if (choice == 0) {
			Constants::COUNTDOWN_SFX->play();
			displayMenu = false;
		}
		else if (choice == 1) {
			STATEMACHINE::getInstance()->changeState(stateTypes::MENU);
		}
		else if (choice == 2) {
			STATEMACHINE::getInstance()->changeState(stateTypes::SETTING);
		}
		isEntered = !isEntered;
	}

	if (cntValue == 0) STATEMACHINE::getInstance()->popState();
}

void CPAUSE::render(sf::RenderWindow* window) {
	background.render(window);
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window->getView().getSize());
	window->draw(backgroundShape);

	if (displayMenu) {
		for (int i = 0; i < maxPauseOpt; ++i) {
			window->draw(option[i]);
		}
		window->draw(cursor);
	}
	else {
		window->draw(countdown);
	}
}

void CPAUSE::moveUp() {
	prevChoice = choice;
	choice = (--choice + maxPauseOpt) % maxPauseOpt;
}

void CPAUSE::moveDown() {
	prevChoice = choice;
	choice = (++choice) % maxPauseOpt;
}

void CPAUSE::countDown(float elapsedTime) {
	if (cntValue > 0 && elapsedTime >= 1.0f) {
		cntValue--;
		if (cntValue == 0) countdown.setString("Now!");
		else  countdown.setString(std::to_string(cntValue));
		clock.restart();
	}
}

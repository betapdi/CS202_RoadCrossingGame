#include "CCREDIT.h"

CCREDIT::CCREDIT()
{
}

CCREDIT::~CCREDIT()
{
}

void CCREDIT::exit()
{
}

void CCREDIT::pause()
{
}

void CCREDIT::resume()
{
}

void CCREDIT::init() {
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

	rrect.setSize(sf::Vector2f(926, 500));
	rrect.setCornersRadius(10);
	rrect.setCornerPointCount(40);
	sf::FloatRect bound = rrect.getGlobalBounds();
	rrect.setOrigin(bound.width / 2, bound.height / 2);
	rrect.setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2);
	rrect.setFillColor(sf::Color(251, 211, 185, 230));

	readFromFile("../Data/Credits.txt");
}

void CCREDIT::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			curWindow->getWindow()->close();
		}
	}
}

void CCREDIT::update(float deltaTime) {
	background.update(deltaTime);
	for (auto button : buttonList) {
		button->update(deltaTime);
	}
}

void CCREDIT::render(sf::RenderWindow* window) {
	background.render(window);
	window->draw(rrect);
	for (auto button : buttonList) {
		button->render(window);
	}
	for (int i = 0; i < maxLines; ++i) {
		window->draw(text[i]);
	}
}

void CCREDIT::readFromFile(const std::string& filename) {
	std::ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		std::cerr << "Unable to open credit file!" << std::endl;
		return;
	}
	for (int i = 0; i < maxLines; ++i) {
		std::string tmp;
		if (std::getline(in, tmp, '\0')) {
			text[i].setString(tmp);
			text[i].setFont(*Constants::INCONSOLATA);
			text[i].setCharacterSize(40);
			text[i].setFillColor(sf::Color::Black);

			sf::FloatRect bounds = text[i].getGlobalBounds();
			text[i].setOrigin(0, bounds.height / 2);
			text[i].setPosition(Constants::SCREEN_WIDTH / 2 - Constants::SCREEN_WIDTH / 3.5, Constants::SCREEN_HEIGHT / 2 + i * 55);
		}
	}
	in.close();
}

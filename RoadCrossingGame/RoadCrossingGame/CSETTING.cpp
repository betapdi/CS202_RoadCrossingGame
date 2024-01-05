#include "CSETTING.h"

CSETTING::CSETTING()
	: resetPressed(0), isFocus(0), isSelected(0), isQuit(0)
	, chooseFocus(0), chooseSelected(0)
{
	prevChoice			= -1;
	direction			= 0;
	selectedCharacter	= nullptr;
	isInit				= true;
	getSetting();
}

CSETTING::~CSETTING() {
}

void CSETTING::exit() {
}

void CSETTING::pause() {
}

void CSETTING::resume() {
}

void CSETTING::init() {
	background.init();

	GBUTTON* button;

	//Quit
	button = new GBUTTON();
	button->init(Constants::QUIT);
	button->setRotation(-20.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(Constants::SCREEN_WIDTH - 1.5 * button->getSize().x, button->getSize().y / 2);
	button->setClickFunction([]() {
		});
	buttonList.push_back(button);

	button = new GBUTTON();
	button->init(Constants::MOVE_LEFT);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(467, 500);
	button->setClickFunction([]() {
		});
	buttonList.push_back(button);	
	
	
	button = new GBUTTON();
	button->init(Constants::MOVE_RIGHT);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(467 + 300, 500);
	button->setClickFunction([]() {
		// do something
		});
	buttonList.push_back(button);	
	
	button = new GBUTTON();
	if (playMusic) {
		button->init(Constants::MUSIC_ON);
	}
	else {
		button->init(Constants::MUSIC_OFF);
	}
	button->setPosition(350, 604);
	button->setClickFunction([]() {
		});
	buttonList.push_back(button);	
	
	button = new GBUTTON();
	if (playSfx) {
		button->init(Constants::SFX_ON);
	}
	else {
		button->init(Constants::SFX_OFF);
	}
	button->setPosition(350 + 290, 604);
	button->setClickFunction([]() {
		});
	buttonList.push_back(button);	
	
	button = new GBUTTON();
	button->init(Constants::RESET);
	button->setPosition(350 + 2 * 290, 604);
	button->setClickFunction([]() {
		// do something
		});
	buttonList.push_back(button);

	text[0].setString("CHOOSE");
	text[1].setString("MUSIC");
	text[2].setString("SFX");
	text[3].setString("RESET");

	for (int i = 0; i < 4; ++i) {
		text[i].setFont(*Constants::LUCKIESTGUY);
		if (i == 0) {
			text[i].setCharacterSize(40);
		}
		else {
			text[i].setCharacterSize(30);
			text[i].setFillColor(sf::Color::Black);
			text[i].setPosition(250 + (i - 1) * 280, 615);
		}
	}
	sf::FloatRect textBounds = text[0].getLocalBounds();
	text[0].setOrigin(textBounds.width / 2, textBounds.height / 2);
	text[0].setPosition((float)Constants::SCREEN_WIDTH/2, 510);
	text[0].setFillColor(sf::Color(251, 211, 185, 255));
	text[0].setOutlineThickness(5);
	text[0].setOutlineColor(sf::Color(119, 52, 59, 255));

	rrect[0].setSize(sf::Vector2f(926, 500));
	rrect[0].setCornersRadius(10);
	rrect[0].setCornerPointCount(40);
	rrect[0].setPosition(177, 70);
	rrect[0].setFillColor(sf::Color(251, 211, 185, 230));	
	
	rrect[1].setSize(sf::Vector2f(926, 70));
	rrect[1].setCornersRadius(10);
	rrect[1].setCornerPointCount(40);
	rrect[1].setPosition(177, 600);
	rrect[1].setFillColor(sf::Color(251, 211, 185, 230));
	
	rrect[2].setSize(sf::Vector2f(387, 62));
	rrect[2].setCornersRadius(10);
	rrect[2].setCornerPointCount(40);
	rrect[2].setPosition(452, 493);
	rrect[2].setFillColor(sf::Color(119, 52, 59, 225));

	//sf::Sprite* player;
	//sf::Vector2u sizeCharacter;
	//player = new sf::Sprite;
	//player->setTexture(*Constants::CHICKEN);
	//player->setScale(0.58f, 0.58f);
	//sizeCharacter = Constants::CHICKEN->getSize();
	//player->setOrigin((sf::Vector2f)sizeCharacter * 0.5f);
	//player->setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 1.8);
	//characters.push_back(player);
	//player = new sf::Sprite;
	//player->setTexture(*Constants::DUCK);
	//player->setScale(0.65, 0.65);
	//sizeCharacter = Constants::DUCK->getSize();
	//player->setOrigin((sf::Vector2f)sizeCharacter * 0.5f);
	//player->setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 1.8);
	////player->setPosition(Constants::SCREEN_WIDTH + 30, Constants::SCREEN_HEIGHT / 2);
	//characters.push_back(player);	
	//
	//player = new sf::Sprite;
	//player->setTexture(*Constants::SQUIRREL);
	//player->setScale(0.55, 0.55);
	//sizeCharacter = Constants::SQUIRREL->getSize();
	//player->setOrigin((sf::Vector2f)sizeCharacter * 0.5f);
	//player->setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 1.8);
	//characters.push_back(player);	
	//
	//player = new sf::Sprite;
	//player->setTexture(*Constants::PENGUIN);
	//player->setScale(0.35, 0.35);
	//sizeCharacter = Constants::PENGUIN->getSize();
	//player->setOrigin((sf::Vector2f)sizeCharacter * 0.5f);
	//player->setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 1.8);
	//characters.push_back(player);	
	//
	//player = new sf::Sprite;
	//player->setTexture(*Constants::CLOWN);
	//player->setScale(1.2, 1.2);
	//sizeCharacter = Constants::CLOWN->getSize();
	//player->setOrigin((sf::Vector2f)sizeCharacter * 0.5f);
	//player->setPosition(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 1.7);
	//characters.push_back(player);

	mCharacters.push_back(new GANIMATION(*Constants::BUNNY,	sf::Vector2i(3, 4), 0.2f));
	mCharacters.push_back(new GANIMATION(*Constants::CAT,	sf::Vector2i(3, 4), 0.2f));
	mCharacters.push_back(new GANIMATION(*Constants::PANDA,	sf::Vector2i(3, 4), 0.2f));
	mCharacters.push_back(new GANIMATION(*Constants::PANDA1,sf::Vector2i(3, 4), 0.2f));
	mCharacters.push_back(new GANIMATION(*Constants::PANDA2,sf::Vector2i(3, 4), 0.2f));

	sf::FloatRect characterBound;
	for (int i = 0; i < 5; ++i) {
		characterBound = mCharacters[i]->getGlobalBounds();
		mCharacters[i]->setOrigin(characterBound.width / 2.0f, characterBound.height / 2.0f);
		mCharacters[i]->setScale(5, 5);
		mCharacters[i]->setPosition(Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 1.8f);
	}

	selectedStamp.setTexture(*Constants::STAMP);
	characterBound = selectedStamp.getGlobalBounds();
	selectedStamp.setOrigin(characterBound.width / 2.0f, characterBound.height / 2.0f);
	selectedStamp.setScale(sf::Vector2f(0.3f, 0.3f));
	selectedStamp.setPosition(Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 2.0f);
	selectedCharacter = mCharacters[cur];
}

void CSETTING::processEvents() {
	sf::Event event;
	while (curWindow->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			curWindow->getWindow()->close();
		}

		if (event.type == sf::Event::MouseMoved) {
			chooseFocus = (text[0].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow())) ? 1 : 0);
		}

		if (event.type == sf::Event::MouseMoved) {
			for (int i = 0; i < 6; ++i) {
				if (buttonList[i]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
					isFocus = true;
					break;
				}
			}
			isFocus = false;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (buttonList[0]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				isQuit = true;
			}
			//Music
			if (buttonList[3]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				playMusic = !playMusic;
				if (!playMusic) {
					buttonList[3]->setTexture(Constants::MUSIC_OFF);
					Constants::ROUND_N_ROUND->stop();
				}
				else {
					buttonList[3]->setTexture(Constants::MUSIC_ON);
					Constants::ROUND_N_ROUND->play();
				}
			}			
			
			//SFX
			if (buttonList[4]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				playSfx = !playSfx;
				if (!playSfx) {
					buttonList[4]->setTexture(Constants::SFX_OFF);
				}
				else {
					buttonList[4]->setTexture(Constants::SFX_ON);
				}
			}

			//Reset
			if (buttonList[5]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				playMusic	= true;
				playSfx		= true;
				cur			= 0;
				chooseID	= 0;
				buttonList[3]->setTexture(Constants::MUSIC_ON);
				buttonList[4]->setTexture(Constants::SFX_ON);
				Constants::ROUND_N_ROUND->play();
			}
			updateSetting();

			//MOVE_LEFT
			if (buttonList[1]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				prevChoice = cur;
				cur = (++cur) % (Constants::maxCharacters);
				direction = -1;
			}

			//MOVE_RIGHT
			if (buttonList[2]->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*curWindow->getWindow()))) {
				prevChoice = cur;
				cur = (--cur + Constants::maxCharacters) % (Constants::maxCharacters);
				direction = 1;
			}

			chooseSelected = (chooseFocus ? 1 : 0);
		}

		selectedCharacter = mCharacters[cur];
		//if (chooseSelected) {
		//	isInit = false;
		//}
	}
}

void CSETTING::update(float deltaTime) {
	background.update(deltaTime);
	mCharacters[cur]->update(deltaTime);

	//if (chooseFocus) {
	//	cursor.loadFromSystem(sf::Cursor::Hand);
	//	curWindow->getWindow()->setMouseCursor(cursor);
	//}

	if (isQuit) {
		updateSetting();
		STATEMACHINE::getInstance()->popState();
	}

	if (chooseFocus) {
		rrect[2].setFillColor(sf::Color(119, 52, 59, 200));
		rrect[2].setSize(sf::Vector2f(388, 64));
	}
	else {
		rrect[2].setFillColor(sf::Color(119, 52, 59, 225));
		rrect[2].setSize(sf::Vector2f(387, 62));
	}

	if (chooseSelected) {
		isInit = false;
		chooseID = cur;
		chooseSelected = !chooseSelected;
	}

	for (auto button : buttonList) {
		button->update(deltaTime);
	}
}

void CSETTING::render(sf::RenderWindow* window) {
	background.render(window);
	for (int i = 0; i < 3; ++i) {
		window->draw(rrect[i]);
	}
	for (auto button : buttonList) {
		button->render(window);
	}
	window->draw(*selectedCharacter);
	if (chooseID == cur) {
		window->draw(selectedStamp);
	}
	for (int i = 0; i < 4; ++i) {
		window->draw(text[i]);
	}
}

void CSETTING::getSetting() {
	std::ifstream fin;
	fin.open("../Data/Setting.txt");
	if (!fin.is_open()) {
		std::cout << "Unable to open Setting File.\n";
		return;
	}
	fin >> cur;
	chooseID = cur;
	fin >> playMusic;
	fin >> playSfx;
	fin.close();
}

void CSETTING::updateSetting() {
	std::ofstream fout;
	fout.open("../Data/Setting.txt", std::ofstream::trunc);
	if (!fout.is_open()) {
		std::cout << "Unable to open Setting File.\n";
		return;
	}
	fout << cur << '\n';
	fout << playMusic << '\n';
	fout << playSfx << '\n';
	fout.close();
}

bool getSFX() {
	std::ifstream fin;
	fin.open("../Data/Setting.txt");
	if (!fin.is_open()) {
		std::cout << "Unable to open Setting File.\n";
		return -1;
	}
	int value;
	std::string x;
	getline(fin, x);
	getline(fin, x);
	fin >> value;
	fin.close();
	return value;
}

bool getMusic() {
	std::ifstream fin;
	fin.open("../Data/Setting.txt");
	if (!fin.is_open()) {
		std::cout << "Unable to open Setting File.\n";
		return -1;
	}
	int value;
	std::string x;
	getline(fin, x);
	fin >> value;
	fin.close();
	return value;
}
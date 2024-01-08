#ifndef PLAYER_H
#define PLAYER_H

#include "Constants.h"
#include <fstream>
#include <string> 
#include "CSETTING.h"

using namespace Constants;

#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT  32

#define DIRECTION_Y_DOWN_INITAL  0
#define DIRETION_Y_LEFT_INITAL  1
#define DIRECTION_Y_RIGHT_INITAL  2
#define DIRECTION_Y_UP_INITAL  3

#define DIRECTION_X_DOWN_INITAL  0
#define DIRECTION_X_LEFT_INITAL 0
#define DIRECTION_X_RIGHT_INITAL 0
#define DIRECTION_X_UP_INITAL  0

bool getSFX();
bool getMusic();

class Player {
public:
	sf::FloatRect getBorder() {
		return sf::FloatRect(_sprite.getPosition(), sf::Vector2f(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height));
	}

	sf::FloatRect getFootBorder() const {
		sf::FloatRect globalBounds = _sprite.getGlobalBounds();
		sf::FloatRect footBounds = globalBounds;

		// Set the height of the footBounds to only cover the bottom part of the player
		float footHeight = 10.0f; // You can adjust this value based on your needs
		footBounds.height = footHeight;
		footBounds.top = globalBounds.top + globalBounds.height - footHeight;

		return footBounds;
	}

	void drawBorder(sf::RenderTarget& target, sf::RenderStates states) const {
		sf::FloatRect footBounds = getFootBorder();

		sf::RectangleShape borderRect;
		borderRect.setSize(sf::Vector2f(footBounds.width, footBounds.height));
		borderRect.setPosition(footBounds.left, footBounds.top);
		borderRect.setFillColor(sf::Color::Transparent);
		borderRect.setOutlineColor(sf::Color::Green); // You can set any color you prefer
		borderRect.setOutlineThickness(2.0f);

		target.draw(borderRect, states);
	}

	void ini(int characterId, float posX = Constants::SCREEN_WIDTH / 2.0f, float posY = Constants::SCREEN_HEIGHT / 2.0f + 100.0f) {
		setTexture(characterId);
		//_sprite.setScale(1.5f, 1.5f);
		_sprite.setPosition(posX, posY);
		hasSFX = getSFX();
	}

	void process(sf::Event &_event) {
		switch (_event.type)
		{
		case sf::Event::Closed:
			curWindow->getWindow()->close();
			exit(1);
		case sf::Event::KeyPressed:
			switch (_event.key.code)
			{
			case sf::Keyboard::Right:
				dir = sf::Keyboard::Right;
				velocity.x = speed;
				break;
			case sf::Keyboard::Left:
				dir = sf::Keyboard::Left;
				velocity.x = -speed;
				break;
			case sf::Keyboard::Up:
				dir = sf::Keyboard::Up;
				velocity.y = -speed;
				break;
			case sf::Keyboard::Down:
				dir = sf::Keyboard::Down;
				velocity.y = speed;
				break;
			}
			if (hasSFX) {
				Constants::MOVE_SFX->setVolume(40);
				Constants::MOVE_SFX->play();
			}
			break;
		case sf::Event::KeyReleased:
			velocity = { 0.0f, 0.0f };
			dir = sf::Keyboard::Unknown;
		}
	}

	void render(sf::RenderWindow* window) {
		//std::cout << "Render player called!!" << std::endl;
		_sprite.setTextureRect(sf::IntRect(source.x * SPRITE_WIDTH, source.y * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT));
		window->draw(_sprite);
		//drawBorder(*window, sf::RenderStates::Default);
	}

	void save(std::ofstream& fout) const {
		fout.write((char*)(&hasSFX), sizeof(bool));
		sf::Vector2f curPos = _sprite.getPosition();
		fout.write((char*)(&curPos.x), sizeof(float));
		fout.write((char*)(&curPos.y), sizeof(float));
	}

	void load(std::ifstream& fin) {
		fin.read((char*)(&hasSFX), sizeof(bool));
		float posX, posY;
		fin.read((char*)(&posX), sizeof(float));
		fin.read((char*)(&posY), sizeof(float));
		std::cout << "Player pos: " << posX << " " << posY << std::endl;
		_sprite.setPosition(posX, posY);
		std::cout << "Current Player: " << getBorder().left << " " << getBorder().top << " " << getBorder().height << std::endl;
	}

	void setTexture(int characterId) {
		switch (characterId) {
		case Characters::Bunny:
			_sprite.setTexture(*BUNNY);
			break;

		case Characters::Cat:
			_sprite.setTexture(*CAT);
			break;

		case Characters::Panda:
			_sprite.setTexture(*PANDA);
			break;

		case Characters::Panda1:
			_sprite.setTexture(*PANDA1);
			break;

		case Characters::Panda2:
			_sprite.setTexture(*PANDA2);
			break;
		}
	}

	sf::View followView(sf::View Camera) {
		
       if(_sprite.getPosition().y<600)
		Camera.move(0.f, float(_sprite.getPosition().y-600));
		return Camera;
	}

	bool explosion(float deltaTime) {
		curTime += deltaTime;
		if (curTime >= frameTime) return 1;
		_sprite.setTexture(*EXPLOSION);
		velocity = { 0.0f,0.0f };
		_sprite.setScale(3.0f, 3.0f);
		source = { 0,0 };
		return 0;
	}

public:
	float curTime = 0.0f, frameTime =0.5f;
	bool hasSFX;
	int score = 0;
	sf::Vector2f velocity = { 0.0f, 0.0f };
	float speed = 200.0f;
	sf::Keyboard::Key dir;
	sf::Sprite _sprite;
	sf::Vector2i source = { 0,0 };

};

#endif
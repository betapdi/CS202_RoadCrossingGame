#ifndef PLAYER_H
#define PLAYER_H

#include "Constants.h"
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


class Player {
public:
	sf::FloatRect getBorder() {
		return _sprite.getGlobalBounds();
	}

	void ini(int characterId) {
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

		_sprite.setPosition(640, 200);
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
	}

	sf::View followView(sf::View Camera) {
		
       if(_sprite.getPosition().y<600)
		Camera.move(0.f, float(_sprite.getPosition().y-600));
		return Camera;
	}

public:
	float curTime = 0.0f, frameTime;
	sf::Vector2f velocity = { 0.0f, 0.0f };
	float speed = 200.0f;
	sf::Keyboard::Key dir;
	sf::Sprite _sprite;
	sf::Vector2i source = { 0,0 };
};
#endif
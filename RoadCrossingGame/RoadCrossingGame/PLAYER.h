#ifndef PLAYER_H
#define PLAYER_H

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
	void ini() {
		_sprite.setTexture(*Constants::BUNNY);
		_sprite.setPosition(640, 200);
	}

	void Mouvment(float deltaTime)
	{
		switch (dir) {
		case sf::Keyboard::Up:
			_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
			if (source.y != DIRECTION_Y_UP_INITAL) {
				source.x = DIRECTION_X_UP_INITAL;
				source.y = DIRECTION_Y_UP_INITAL;
			}
			if (source.x >= 2)
				source.x = DIRECTION_X_UP_INITAL;
			else source.x++;
			break;
		case sf::Keyboard::Down:
			_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
			if (source.y != DIRECTION_Y_DOWN_INITAL) {
				source.x = DIRECTION_X_DOWN_INITAL;
				source.y = DIRECTION_Y_DOWN_INITAL;
			}
			if (source.x >= 2)
				source.x = DIRECTION_X_DOWN_INITAL;
			else source.x++;

			break;
		case sf::Keyboard::Right:
			_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
			if (source.y != DIRECTION_Y_RIGHT_INITAL) {
				source.x = DIRECTION_X_RIGHT_INITAL;
				source.y = DIRECTION_Y_RIGHT_INITAL;
			}
			if (source.x >= 2)
				source.x = DIRECTION_X_RIGHT_INITAL;
			else source.x++;
			break;
		case sf::Keyboard::Left:
			_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
			if (source.y != DIRETION_Y_LEFT_INITAL) {
				source.x = DIRECTION_X_LEFT_INITAL;
				source.y = DIRETION_Y_LEFT_INITAL;
			}
			if (source.x >= 2)
				source.x = DIRECTION_X_LEFT_INITAL;
			else source.x++;
			break;
		}
	}

	void process() {
		sf::Event _event;
		while (curWindow->getWindow()->pollEvent(_event))
		{
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
	}
	void render(sf::RenderWindow* window) {
		_sprite.setTextureRect(sf::IntRect(source.x * SPRITE_WIDTH, source.y * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT));
		window->draw(_sprite);
	}

	sf::View followView(sf::View Camera) {
		
       if(_sprite.getPosition().y<600)
		Camera.move(0.f, float(_sprite.getPosition().y-600));
		return Camera;
	}
private:
	sf::Vector2f velocity = { 0.0f, 0.0f };
	float speed = 200.0f;
	sf::Keyboard::Key dir;
	sf::Sprite _sprite;
	sf::Vector2i source = { 0,0 };
};
#endif
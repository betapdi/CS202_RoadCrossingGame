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
	}
	void Mouvment(const int& dir)
	{
		switch (dir) {
		case 0:
			_sprite.move(sf::Vector2f(0, -8));
			break;
		case 1:
			_sprite.move(sf::Vector2f(0, 8));
			break;
		case 2:
			_sprite.move(sf::Vector2f(8, 0));
			break;
		case 3:
			_sprite.move(sf::Vector2f(-8, 0));
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
					Mouvment(2);
					if (source.y != DIRECTION_Y_RIGHT_INITAL) {
						source.x = DIRECTION_X_RIGHT_INITAL;
						source.y = DIRECTION_Y_RIGHT_INITAL;
					}
					if (source.x >= 2)
						source.x = DIRECTION_X_RIGHT_INITAL;
					else source.x++;

					break;
				case sf::Keyboard::Left:
					Mouvment(3);
					if (source.y != DIRETION_Y_LEFT_INITAL) {
						source.x = DIRECTION_X_LEFT_INITAL;
						source.y = DIRETION_Y_LEFT_INITAL;
					}
					if (source.x >= 2)
						source.x = DIRECTION_X_LEFT_INITAL;
					else source.x++;

					break;
				case sf::Keyboard::Up:
					Mouvment(0);
					if (source.y != DIRECTION_Y_UP_INITAL) {
						source.x = DIRECTION_X_UP_INITAL;
						source.y = DIRECTION_Y_UP_INITAL;
					}
					if (source.x >= 2)
						source.x = DIRECTION_X_UP_INITAL;
					else source.x++;

					break;
				case sf::Keyboard::Down:
					Mouvment(1);
					if (source.y != DIRECTION_Y_DOWN_INITAL) {
						source.x = DIRECTION_X_DOWN_INITAL;
						source.y = DIRECTION_Y_DOWN_INITAL;
					}
					if (source.x >= 2)
						source.x = DIRECTION_X_DOWN_INITAL;
					else source.x++;

					break;
					break;
				}
				break;
			}
		}
	}
	void render(sf::RenderWindow* window) {
		_sprite.setTextureRect(sf::IntRect(source.x * SPRITE_WIDTH, source.y * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT));
		window->draw(_sprite);
	}
private:


	sf::Sprite _sprite;
	sf::Vector2i source = { 0,0 };
};
#endif
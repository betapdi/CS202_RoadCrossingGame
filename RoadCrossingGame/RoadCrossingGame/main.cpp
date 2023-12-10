#include "CGAME.h"
#include "GANIMATION.h"
#include "CASSET.h"
#include "COBJECT.h"

int main() {
    CGAME crossy_road;
    crossy_road.run();

 /*   sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Animation");

    sf::Texture texture = *CASSET::getInstance()->GetTexture("Ride.png");

    sf::RectangleShape car;
    GANIMATION carMove(texture, sf::Vector2i(8, 1), 0.3f);
    car.setSize(sf::Vector2f(300, 300));
    car.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT / 2 - Constants::SCREEN_HEIGHT / 8));
    car.setTexture(&texture);


    COBJECT road(CASSET::getInstance()->m_textures["static_street_dotted_horizontal"]);
    road.createDummyMap(Constants::SCREEN_WIDTH);

    sf::Clock clock;
    float deltaTime = 0;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        carMove.update(0, deltaTime);
        car.setTextureRect(carMove.uvRect);
        car.move(150 * deltaTime, 0);
        if (car.getPosition().x >= Constants::SCREEN_WIDTH - 5) {
            car.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT / 2 - Constants::SCREEN_HEIGHT / 8));
        }
        
        window.clear(sf::Color::White);
        window.draw(car);
        road.draw(&window);
        window.display();
    }*/
	return 0;
}
#include "CGAME.h"
#include "GANIMATION.h"
#include "CASSET.h"

int main() {
    CGAME crossy_road;
    crossy_road.run();
    //sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Animation");
    //sf::Texture texture = *CASSET::getInstance()->GetTexture("Ride.bmp");
    //GANIMATION ani(texture, sf::Vector2i(8, 1), 0.1f);
    //ani.setScale(2, 2);

    //sf::Clock clock;
    //float deltaTime = 0;
    //while (window.isOpen()) {
    //    deltaTime = clock.restart().asSeconds();
    //    sf::Event event;
    //    while (window.pollEvent(event)) {
    //        if (event.type == sf::Event::Closed) {
    //            window.close();
    //        }
    //    }
    //    ani.update(deltaTime);
    //    window.clear(sf::Color::White);
    //    window.draw(ani);
    //    window.display();
    //}
	return 0;
}
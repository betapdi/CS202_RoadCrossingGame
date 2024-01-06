#include "CGAME.h"
#include "GANIMATION.h"
#include "CASSET.h"
#include "COBJECT.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
int main() {
    srand(time(0));
    CGAME crossy_road;
    crossy_road.run();

   // sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Animation");

   // sf::Texture texture = *CASSET::getInstance()->GetTexture("quickSand.png");

   ///* TextureHolder mTexture;
   // mTexture.load(Textures::MONEY, "Media/Textures/money.png");*/

   // sf::RectangleShape car;
   // GANIMATION carMove(texture, sf::Vector2i(8, 1), 0.1f);
   // carMove.setScale(2, 2);
   // sf::Clock clock;
   // float deltaTime = 0;
   // //sf::Time timeSinceLastUpdate = sf::Time::Zero;
   // while (window.isOpen()) {
   //     deltaTime = clock.restart().asSeconds();
   //     sf::Event event;
   //     while (window.pollEvent(event)) {
   //         if (event.type == sf::Event::Closed) {
   //             window.close();
   //         }
   //     }
   //     carMove.update(deltaTime);
   //     carMove.move(250 * deltaTime, 0);
   //     window.clear(sf::Color::White);
   //     window.draw(carMove);
   //     //window.draw(car);
   //     window.display();
   // }
	return 0;
}
#include "CGAME.h"
#include "GANIMATION.h"
#include "CASSET.h"
#include "COBJECT.h"

int main() {
    CGAME crossy_road;
    crossy_road.run();

    //sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Animation");

    //sf::Texture texture = *CASSET::getInstance()->GetTexture("Ride.png");

    //sf::RectangleShape car;
    //GANIMATION carMove(texture, sf::Vector2i(8, 1), 0.3f);
    //car.setSize(sf::Vector2f(300, 300));
    //car.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT / 2 - Constants::SCREEN_HEIGHT / 8));
    //car.setTexture(&texture);

    //sf::Texture texture1 = *CASSET::getInstance()->m_textures["static_street_dotted_horizontal"];
    //texture1.setRepeated(true);    
    //
    //sf::Texture texture2 = *CASSET::getInstance()->m_textures["static_street"];
    //texture2.setRepeated(true);    
    //
    //sf::Texture laneText = *Constants::INNER_LANE;
    //sf::Texture topLane = *Constants::TOP_LANE;
    //sf::Texture startLane = *Constants::START_LANE;
    //laneText.setRepeated(true);
    //topLane.setRepeated(true);
    //startLane.setRepeated(true);

    //sf::RectangleShape sprite;
    //sprite.setTexture(&texture1);
    //sprite.setSize(sf::Vector2f(1200, 32));
    //sprite.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE/2});
    //sprite.setScale(2.f, 1.f);
    //sprite.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 4.5));    
    //
    //sf::RectangleShape sprite1;
    //sprite1.setTexture(&texture2);
    //sprite1.setSize(sf::Vector2f(1200, 32));
    //sprite1.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE/2});
    //sprite1.setScale(2.f, 1.f);
    //sprite1.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 4.5 + 32));    
    //
    //sf::RectangleShape sprite2;
    //sprite2.setTexture(&texture2);
    //sprite2.setSize(sf::Vector2f(1200, 32));
    //sprite2.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE/2});
    //sprite2.setScale(2.f, 1.f);
    //sprite2.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 4.5 - 32));    
    //
    //
    //sf::RectangleShape laneRect;
    //laneRect.setTexture(&laneText);
    //laneRect.setSize(sf::Vector2f(1200, 32));
    //laneRect.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE/2});
    //laneRect.setScale(2.f, 1.f);
    //laneRect.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 4.5 - 32 * 3));
    //
    //sf::RectangleShape startRect;
    //startRect.setTexture(&startLane);
    //startRect.setSize(sf::Vector2f(1200, 32));
    //startRect.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE/2});
    //startRect.setScale(2.f, 1.f);
    //startRect.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 4.5 - 32 * 2));
    //
    //sf::RectangleShape topRect;
    //topRect.setTexture(&topLane);
    //topRect.setSize(sf::Vector2f(1200, 32));
    //topRect.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE/2});
    //topRect.setScale(2.f, 1.f);
    //topRect.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT - Constants::SCREEN_HEIGHT / 4.5 - 32 * 4));


    //COBJECT road(CASSET::getInstance()->m_textures["static_street_road_markings_left"], sf::Vector2f(0, 200));
    //road.createDummyMap(Constants::SCREEN_WIDTH);    
    //
    //COBJECT first_road(CASSET::getInstance()->m_textures["static_street_dotted_horizontal"], sf::Vector2f(0, 532));
    //first_road.createDummyMap(Constants::SCREEN_WIDTH);

    //sf::Clock clock;
    //float deltaTime = 0;
    //sf::Time timeSinceLastUpdate = sf::Time::Zero;
    //while (window.isOpen()) {
    //    deltaTime = clock.restart().asSeconds();
    //    sf::Event event;
    //    while (window.pollEvent(event)) {
    //        if (event.type == sf::Event::Closed) {
    //            window.close();
    //        }
    //    }

    //    carMove.update(0, deltaTime);
    //    car.setTextureRect(carMove.uvRect);
    //    car.move(150 * deltaTime, 0);
    //    if (car.getPosition().x >= Constants::SCREEN_WIDTH - 5) {
    //        car.setPosition(sf::Vector2f(0, Constants::SCREEN_HEIGHT / 2 - Constants::SCREEN_HEIGHT / 8));
    //    }
    //    
    //    window.clear(sf::Color::White);
    //    window.draw(sprite);
    //    window.draw(sprite1);
    //    window.draw(sprite2);
    //    window.draw(laneRect);
    //    window.draw(startRect);
    //    window.draw(topRect);
    //    window.draw(car);
    //    //road.draw(&window);
    //    //first_road.draw(&window);
    //    window.display();
    //}
	return 0;
}
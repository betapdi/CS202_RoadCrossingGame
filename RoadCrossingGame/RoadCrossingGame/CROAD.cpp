#include "CROAD.h"
#include "CRESOURCEHOLDER.h"
#include "Constants.h"

Textures::ID toTextureID(CROAD::roadTypes type) {
	switch (type) {
	case CROAD::DEFAULT_ROAD:
		return Textures::DEFAULT_ROAD;

	case CROAD::DOTTED_ROAD:
		return Textures::DOTTED_ROAD;
	}
}
//CROAD::CROAD(Type type, const TextureHolder& textures, float posY) {
//	mType = type;
//
//	rectText = textures.get(toTextureID(type));
//	rectText.setRepeated(true);
//
//	mRect.setTexture(&rectText);
//	mRect.setTextureRect({ 0, 0, Constants::SCREEN_WIDTH, Constants::ROAD_SIZE / 2 });
//	mRect.setSize(sf::Vector2f(Constants::SCREEN_WIDTH, Constants::ROAD_SIZE));
//	mRect.setScale(sf::Vector2f(Constants::SCALE_OF_ROAD, 1.0f));
//	mRect.setPosition(sf::Vector2f(0, posY));
//}

CROAD::CROAD(const sf::Texture& texture, const sf::IntRect& textureRect)
{
	mRect.setTexture(&texture);
	mRect.setTextureRect(textureRect);
	mRect.setSize(sf::Vector2f(Constants::SCREEN_WIDTH, Constants::ROAD_SIZE));
}

CROAD::CROAD(roadTypes type, const TextureHolder& textures, const sf::IntRect& textureRect) {
	mType = type;
	sf::Texture getTexture;
	getTexture = textures.get(toTextureID(type));
	getTexture.setRepeated(true);
	mRect.setTexture(&getTexture);
	mRect.setTextureRect(textureRect);
	mRect.setSize(sf::Vector2f(Constants::SCREEN_WIDTH, Constants::ROAD_SIZE));
}

void CROAD::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mRect, states);
}

#include "CROAD.h"
#include "CRESOURCEHOLDER.h"
#include "Constants.h"

Textures::ID toTextureID(CROAD::roadTypes type) {
	switch (type) {
	case CROAD::DEFAULT_ROAD:
		return Textures::DEFAULT_ROAD;
		break;
	case CROAD::DOTTED_ROAD:
		return Textures::DOTTED_ROAD;
		break;
	case CROAD::PAVEMENT:
		return Textures::PAVEMENT;
		break;
	case CROAD::RAIL_ROAD:
		return Textures::RAIL_ROAD;
		break;
	case CROAD::WATER:
		return Textures::WATER;
		break;
	case CROAD::GROUND:
		return Textures::GROUND;
		break;
	}
}

CROAD::roadTypes fromIntToType(int type) {
	switch (type) {
	case 0:
		return CROAD::DEFAULT_ROAD;
		break;
	case 1:
		return CROAD::DOTTED_ROAD;
		break;
	case 2:
		return CROAD::PAVEMENT;
		break;
	case 3:
		return CROAD::RAIL_ROAD;
		break;
	case 4:
		return CROAD::WATER;
		break;
	case 5:
		return CROAD::GROUND;
		break;
	}
}

CROAD::CROAD(const sf::Texture& texture, const sf::IntRect& textureRect) {
	mRect.setTexture(&texture);
	mRect.setTextureRect(textureRect);
	mRect.setSize(sf::Vector2f(Constants::SCREEN_WIDTH, Constants::ROAD_SIZE));
	//mRect.setOutlineThickness(0.5f);
	//mRect.setOutlineColor(sf::Color::White);
}

CROAD::CROAD(int type, const TextureHolder& textures, const sf::IntRect& textureRect) {
	mType = fromIntToType(type);
	mRect.setTexture(&textures.get(toTextureID(mType)));
	mRect.setTextureRect(textureRect);
	mRect.setSize(sf::Vector2f(Constants::SCREEN_WIDTH, Constants::ROAD_SIZE));
}

void CROAD::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mRect, states);
}

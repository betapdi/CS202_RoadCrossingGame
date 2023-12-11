#include "CSPRITENODE.h"

CSPRITENODE::CSPRITENODE(const sf::Texture& texture)
	: mSprite(texture) {
}

CSPRITENODE::CSPRITENODE(const sf::Texture& texture, const sf::IntRect& textureRect)
	: mSprite(texture, textureRect) {
}

void CSPRITENODE::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}
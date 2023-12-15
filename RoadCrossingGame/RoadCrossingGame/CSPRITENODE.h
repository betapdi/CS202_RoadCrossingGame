#ifndef CSPRITENODE_H
#define CSPRITENODE_H

#include "CENTITY.h"
class CSPRITENODE : public CENTITY {
public:
	explicit CSPRITENODE(const sf::Texture& texture);
	CSPRITENODE(const sf::Texture& texture, const sf::IntRect& textureRect);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Sprite mSprite;
};

#endif // !CSPRITENODE_H
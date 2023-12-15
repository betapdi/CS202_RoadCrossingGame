#ifndef CROAD_H
#define CROAD_H

#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"

class CROAD : public CENTITY {
public:
	enum roadTypes {
		DEFAULT_ROAD,
		DOTTED_ROAD,
		PAVEMENT,
		RAIL_ROAD,
		WATER,
		GROUND,
	};
public:
	CROAD(const sf::Texture& texture, const sf::IntRect& textureRect);
	CROAD(int type, const TextureHolder& textures, const sf::IntRect& textureRect);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	roadTypes mType;
	sf::RectangleShape mRect;
};

#endif // !CROAD_H
#ifndef CROAD_H
#define CROAD_H

#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"

class CROAD : public CENTITY {
public:
	CROAD(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape mRect;
};

#endif // !CROAD_H
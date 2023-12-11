#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"
#include <SFML/Graphics/Sprite.hpp>

class Aircraft : public CENTITY
{
public:
	enum Type
	{
		Eagle,
		Raptor,
		Default_road,
	};


public:
	Aircraft(Type type, const TextureHolder& textures);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite	mSprite;
};

#endif // !AIRCRAFT_H
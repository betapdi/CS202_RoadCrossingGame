#ifndef CANIMAL_H
#define CANIMAL_H
#include "RESOURCEIDENTIFIER.h"
#include "CENTITY.h"
#include "GANIMATION.h"
#include <SFML/Graphics/Sprite.hpp>
class CANIMAL : public CENTITY {
public:
	enum Animal {

	};
public:
	CANIMAL(Animal type, const TextureHolder& textures);
private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Animal mType;
	sf::Sprite mSprite;
};
#endif // !CANIMAL_H

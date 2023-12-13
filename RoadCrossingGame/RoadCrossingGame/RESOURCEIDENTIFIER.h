#ifndef RESOURCEIDENTIFIER_H
#define RESOURCEIDENTIFIER_H

namespace sf 
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
		DEFAULT_ROAD,
		DOTTED_ROAD,
		RAIL_ROAD,
		PAVEMENT,
		FAST_FOOD_STORE,
		COFFEE_SHOP,
		GROCERY,
		SHOP,
		BARBER_SHOP,
		BREAD_SHOP,
		VEGETABLE_SHOP,
		HOUSE,
		BLUE_SIGN,
		GREEN_SIGN,
		WHITE_SIGN,
		VENDING_MACHINE,
		GRASS,
	};
}
template <typename Resource, typename Identifier>

class CRESOURCEHOLDER;
typedef CRESOURCEHOLDER<sf::Texture, Textures::ID> TextureHolder;
#endif // !RESOURCEIDENTIFIER_H

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
		PAVEMENT,
		RAIL_ROAD,
		WATER,
		GROUND,
		SMALL_TREE,
		BIG_TREE,
		BENCH,
		VENDING_MACHINE,
		BLUE_SIGN,
		GREEN_SIGN,
		WHITE_SIGN,
		HOTDOG,
		LIGHT,
		GROCERY,
		SHOP,
		HOUSE,
		MONEY,
		BEAR_LEFT,
		BEAR_RIGHT,
		DEER_L,
		DEER_R,
		REINDEER_L,
		REINDEER_R,
		FOX_L,
		FOX_R,
		WOLF_L,
		WOLF_R,
	};
}
template <typename Resource, typename Identifier>

class CRESOURCEHOLDER;
typedef CRESOURCEHOLDER<sf::Texture, Textures::ID> TextureHolder;
#endif // !RESOURCEIDENTIFIER_H

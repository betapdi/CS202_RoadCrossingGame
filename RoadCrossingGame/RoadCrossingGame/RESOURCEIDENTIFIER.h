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
		TRAFFIC_LIGHT,
		BLUE_CAR_L,
		BLUE_CAR_R,
		GREEN_CAR_L,
		GREEN_CAR_R,
		//ORANGE_CAR_L,
		//ORANGE_CAR_R,
		RED_CAR_L,
		RED_CAR_R,
		POLICE_CAR_L,
		POLICE_CAR_R,
		BLUE_TRUCK_L,
		BLUE_TRUCK_R,
		TRUCK_L,
		TRUCK_R,
		//BUS_L,
		//BUS_R,
		OLD_TRAIN_L,
		OLD_TRAIN_R,
		TRAIN_L,
		TRAIN_R,
	};
}
template <typename Resource, typename Identifier>

class CRESOURCEHOLDER;
typedef CRESOURCEHOLDER<sf::Texture, Textures::ID> TextureHolder;
#endif // !RESOURCEIDENTIFIER_H

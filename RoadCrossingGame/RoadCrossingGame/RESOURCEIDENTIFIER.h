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
	};
}
template <typename Resource, typename Identifier>

class CRESOURCEHOLDER;
typedef CRESOURCEHOLDER<sf::Texture, Textures::ID> TextureHolder;
#endif // !RESOURCEIDENTIFIER_H
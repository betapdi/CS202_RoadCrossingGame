#ifndef GWORLD_H
#define GWORLD_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include <array>
#include <deque>
#include "Aircraft.h"
#include "Constants.h"

namespace sf {
	class RenderWindow;
}

class GWORLD {
public:
	explicit GWORLD(sf::RenderWindow& window);
	void update(float deltaTime);
	void draw();
private:
	void loadTextures();
	void buildMaps();
	//void adaptPlayerPosition();
	//void adaptPlayerVelocity();
	//sf::FloatRect getViewBounds() const;


private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;


	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	std::deque<GMAP> mMaps;
};

#endif // !GWORLD_H
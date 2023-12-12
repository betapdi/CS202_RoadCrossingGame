#ifndef GWORLD_H
#define GWORLD_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include "GMAP.h"
#include <vector>
#include "Aircraft.h"
#include "Constants.h"

namespace sf {
	class RenderWindow;
}

using namespace Constants;

class GWORLD {
public:
	explicit GWORLD(sf::RenderWindow& window);
	void update(float deltaTime);
	void draw();
private:
	void loadTextures();
	void buildMaps();
	void buildPlayer();
	void handleMapOutOfWorld(float deltaTime);
	GMAP* getCurrentMap();
	//void adaptPlayerPosition();
	//void adaptPlayerVelocity();
	//sf::FloatRect getViewBounds() const;

private:
	sf::RenderWindow& mWindow;
	TextureHolder mTextures;

	CSCENENODE mSceneGraph;
	std::vector<CSCENENODE*> mSceneLayers;

	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	std::vector<GMAP> mMaps;
	std::vector<int> id;
};

#endif // !GWORLD_H
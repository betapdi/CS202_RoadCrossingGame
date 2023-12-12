#ifndef GMAP_H
#define GMAP_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include <vector>
#include "Aircraft.h"
#include "Constants.h"

using namespace Constants;

namespace sf {
	class RenderWindow;
}

class GMAP {
public:
	GMAP(sf::RenderWindow& window, const int& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures);
	void update(float deltaTime);
	void draw();

	sf::Vector2f getCoordinate();
	void rebuild(const int& yMapCoordinate);
	void handleTouchBorder(Aircraft* mPlayerAircraft);

private:
	void buildScene();
	void generateRoads();
	//void adaptPlayerPosition();
	//void adaptPlayerVelocity();
	//sf::FloatRect getViewBounds() const;

private:
	sf::RenderWindow& mWindow;

	TextureHolder* mTextures;
	std::vector<CSCENENODE*>* mSceneLayers;
	CSCENENODE* mSceneGraph;

	sf::FloatRect mWorldBounds;
	sf::FloatRect mRoadBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
};

#endif // !GMAP_H
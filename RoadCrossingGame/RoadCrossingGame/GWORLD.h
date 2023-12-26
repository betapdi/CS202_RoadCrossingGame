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
#include "PLAYER.h"

namespace sf {
	class RenderWindow;
}

using namespace Constants;

class GWORLD {
public:
	explicit GWORLD(sf::RenderWindow& window);
	void update(float deltaTime);
	void draw();
	void processEvents(sf::Event& event);
private:
	void loadTextures();
	void buildMaps();
	void buildPlayer();
	void handleMapOutOfWorld(float deltaTime);
	void handlePlayerOutOfWorld(float deltaTime);
	GMAP* getCurrentMap();
	void playerMovement(float deltaTime);
	bool isCollided(sf::Sprite& sprite, const float& deltaTime);

	//void generateRoads();
	//void generateObstacle();
	//void generatePosition(bool isInit);

public:
	std::vector<std::pair<sf::Vector2f, int>> mapPos;

private:
	sf::RenderWindow& mWindow;
	TextureHolder mTextures;
	sf::View mWorldView;

	Player player;

	CSCENENODE worldSceneGraph[3];
	std::vector<CSCENENODE*> worldSceneLayers[3];

	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	std::vector<GMAP> mMaps;
	std::vector<int> id;

	//
	bool isInit;
	bool isLoss;
};

#endif // !GWORLD_H
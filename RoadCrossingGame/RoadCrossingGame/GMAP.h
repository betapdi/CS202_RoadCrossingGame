#ifndef GMAP_H
#define GMAP_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include "CANIMAL.h"
#include "COBJECT.h"
#include <vector>
#include "Aircraft.h"
#include <algorithm>
#include "Constants.h"
#include <queue>

using namespace Constants;

namespace sf {
	class RenderWindow;
}

class GMAP {
public:
	GMAP(sf::RenderWindow& window, const float& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures, float* mScrollSpeed);
	void update(float deltaTime);
	void draw();

	sf::Vector2f getCoordinate();
	void rebuild(const float& yMapCoordinate);
	void handleTouchBorder(Aircraft* mPlayerAircraft);
private:
	void buildScene();
	void generateRoads();
	//void adaptPlayerPosition();
	//void adaptPlayerVelocity();
	//sf::FloatRect getViewBounds() const;
	void generateObstacle(bool isInit);
	void generatePosition(bool isInit);
	void generateAnimals();
	void generateTrafficLight();
private:
	sf::RenderWindow& mWindow;
	TextureHolder* mTextures;
	std::vector<CSCENENODE*>* mSceneLayers;
	CSCENENODE* mSceneGraph;
	std::vector<CANIMAL*> mAnimal;
	std::vector<COBJECT*> mTrafficLight;
	bool isInit;
	std::vector<std::pair<sf::Vector2f, int>> mapPos;
	sf::FloatRect mWorldBounds;
	sf::FloatRect mRoadBounds;
	sf::Vector2f mSpawnPosition;
	float* mScrollSpeed;
	float yCoor;
};

#endif // !GMAP_H
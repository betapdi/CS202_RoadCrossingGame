#ifndef GMAP_H
#define GMAP_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include "CANIMAL.h"
#include "COBJECT.h"
#include "CMONEY.h"
#include "COBSTACLE.h"
#include "CVEHICLE.h"
#include <vector>
#include "Aircraft.h"
#include <algorithm>
#include "Constants.h"
#include <queue>
#include "PLAYER.h"
#include <time.h>

using namespace Constants;

namespace sf {
	class RenderWindow;
}

class GMAP {
public:
	GMAP(sf::RenderWindow& window, const float& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures, float* mScrollSpeed, bool* isLoss, bool* isInit, Player* player, int* score);
	void update(float deltaTime);
	void draw();

	sf::Vector2f getCoordinate();
	void rebuild(const float& yMapCoordinate, bool isInit);
	bool isCollided(sf::FloatRect &border);
	void setSFXAllow(bool isAllowed);
	void savePos(std::ofstream& fout);
	void saveCharacterID(std::ofstream& fout);
	void loadPos(std::ifstream& fin);
private:
	void buildScene(bool isInit);
	void generateRoads();
	void generateInitialObstacle();
	void generateObstacle(bool isInit);
	void generatePosition(bool isInit);
	void generateAnimals();
	void generateVehicles();
	void generateCars();
	void generateTrafficLight();
	void generateMoney();
	void checkLose(float deltaTime);
	void checkMoney();
	void generateTrain();
	void handleTrafficLightChange();
private:
	sf::RenderWindow& mWindow;
	TextureHolder* mTextures;
	Player* player;

	std::vector<CSCENENODE*>* mSceneLayers;
	CSCENENODE* mSceneGraph;

	std::vector<CANIMAL*> mAnimal;
	std::vector<COBJECT*> mTrafficLight;
	std::vector<COBSTACLE*> mObstacle;
	std::vector<CMONEY*> mMoney;
	//static bool isInit;
	bool* isLoss;
	bool hasSFX;

	std::vector<CVEHICLE*> mVehicle;
	std::vector<CVEHICLE*> mTrain;
	std::vector<CVEHICLE*> mTrainTail;
	bool isInit;
	std::vector<std::pair<sf::Vector2f, int>> mapPos;
	sf::FloatRect mWorldBounds;
	sf::FloatRect mRoadBounds;
	sf::Vector2f mSpawnPosition;

	float* mScrollSpeed;
	float yCoor;

	int* score;
};

#endif // !GMAP_H
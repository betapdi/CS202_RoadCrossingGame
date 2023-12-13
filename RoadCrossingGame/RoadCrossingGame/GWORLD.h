#ifndef GWORLD_H
#define GWORLD_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include "COBSTACLE.h"
#include <array>
#include "Aircraft.h"
#include "Constants.h"

namespace sf {
	class RenderWindow;
}

class GWORLD : private sf::NonCopyable {
public:
	explicit GWORLD(sf::RenderWindow& window);
	void update(float deltaTime);
	void draw();
private:
	void loadTextures();
	void buildScene();
	void generateRoads();
	void generateObstacle();
	void generatePosition(bool isInit);
private:
	enum Layer
	{
		Background,
		Road,
		Obstacle,
		Air,
		LayerCount
	};


private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;

	CSCENENODE mSceneGraph;
	std::array<CSCENENODE*, LayerCount>	mSceneLayers;

	bool isInit;
	std::vector<std::pair<sf::Vector2f, int>> mapPos;

	sf::FloatRect mWorldBounds;
	sf::FloatRect mRoadBounds;
	std::vector<sf::FloatRect> mWorlds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};

#endif // !GWORLD_H
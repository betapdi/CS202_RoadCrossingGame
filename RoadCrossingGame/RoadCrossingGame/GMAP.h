#ifndef GMAP_H
#define GMAP_H

#include "CSCENENODE.h"
#include "CSPRITENODE.h"
#include "RESOURCEIDENTIFIER.h"
#include "CRESOURCEHOLDER.h"
#include "CROAD.h"
#include <array>
#include "Aircraft.h"
#include "Constants.h"

namespace sf {
	class RenderWindow;
}

class GMAP : private sf::NonCopyable {
public:
	explicit GMAP(sf::RenderWindow& window);
	void update(float deltaTime);
	void draw();
private:
	void loadTextures();
	void buildScene();
	void generateRoads();
	//void adaptPlayerPosition();
	//void adaptPlayerVelocity();
	//sf::FloatRect getViewBounds() const;
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

	sf::FloatRect mWorldBounds;
	sf::FloatRect mRoadBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};

#endif // !GMAP_H
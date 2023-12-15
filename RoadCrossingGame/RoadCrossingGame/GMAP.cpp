#include "GMAP.h"
#include <iomanip>
#include "Others.h"

GMAP::GMAP(sf::RenderWindow& window, const float& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures, float* mScrollSpeed)
	: mWindow(window)
	, mWorldBounds(0.f, yMapCoordinate, SCREEN_WIDTH, SCREEN_HEIGHT)
	, mRoadBounds(0.f, 0.f, window.getDefaultView().getSize().x, Constants::ROAD_SIZE)
	, mScrollSpeed(mScrollSpeed)
	, yCoor(yMapCoordinate)
{
	this->mSceneGraph = mSceneGraph;
	this->mSceneLayers = mSceneLayers;
	this->mTextures = mTextures;

	std::cout << this->mSceneLayers->size() << std::endl;
	buildScene();
}

sf::Vector2f GMAP::getCoordinate() {
	return sf::Vector2f(mWorldBounds.left, mWorldBounds.top);
}

void GMAP::rebuild(const float& lastYCoordinate) {
	mWorldBounds.top = lastYCoordinate - SCREEN_HEIGHT;
	for (std::size_t i = 0; i < LayerCount - 1; ++i) {
		mSceneLayers->at(i)->clear();
	}

	buildScene();
}

void GMAP::handleTouchBorder(Aircraft* mPlayerAircraft) {

}

void GMAP::update(float deltaTime)
{	
	mSceneGraph->update(deltaTime);
}

void GMAP::draw() {}

void GMAP::buildScene()
{
	generatePosition(isInit);
	generateRoads();
	generateObstacle();
}

void GMAP::generatePosition(bool isInit) {
	if (isInit) {
		for (int i = 0; i < 3; ++i) {
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - i * Constants::ROAD_SIZE), 3));
		}
		for (int i = mWorldBounds.top + mWorldBounds.height - 3 * Constants::ROAD_SIZE; i >= mWorldBounds.top; i -= Constants::ROAD_SIZE) {
			int isRoad = randBiasedInt(0, 3, 0.5);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
		isInit = !isInit;
	}
	else {
		for (int i = mWorldBounds.top + mWorldBounds.height; i >= mWorldBounds.top; i -= Constants::ROAD_SIZE) {
			int isRoad = randBiasedInt(0, 3, 0.5);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
	}
	std::cout << "Position:" << std::endl;
	for (int i = 0; i < mapPos.size(); ++i) {
		std::cout << mapPos[i].first.x << " - " << mapPos[i].first.y << std::endl;
	}
}

void GMAP::generateRoads() {
	for (int i = 0; i < mapPos.size(); ++i) {
		sf::IntRect textureRect1(mRoadBounds);
		sf::Texture* mText = nullptr;
		switch (mapPos[i].second) {
		case 0:
			mText = &mTextures->get(Textures::DEFAULT_ROAD);
			break;
		case 1:
			mText = &mTextures->get(Textures::GROUND);
			break;
		case 2:
			mText = &mTextures->get(Textures::RAIL_ROAD);
			break;
		case 3:
			mText = &mTextures->get(Textures::PAVEMENT);
			break;
		case 4:
			mText = &mTextures->get(Textures::WATER);
			break;
		}
		mText->setRepeated(true);
		if (mText) {
			std::unique_ptr<CROAD> road(new CROAD(*mText, textureRect1));
			road->setPosition(mapPos[i].first);
			mSceneLayers->at(Road)->attachChild(std::move(road));
		}
	}
}

void GMAP::generateObstacle() {
	for (int i = mapPos.size() - 1; i >= 0; --i) {
		if (mapPos[i].second == 3) {
			int numOfObstacle = randBiasedInt(4, Constants::maxObstacle, 0.4f);
			for (int j = 0; j < numOfObstacle; ++j) {
				int startPos = j * (mWorldBounds.width / numOfObstacle);
				int endPos = startPos + mWorldBounds.width / numOfObstacle;
				std::cout << startPos << std::endl;
				std::cout << endPos << std::endl;
				int type = randObject(0, Constants::maxObstacle, 0.5f);

				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
				obstacle->setPosition(randInt(startPos, endPos) + 50, mapPos[i].first.y + 54);
				//std::cout << "Pos: " << obstacle->getPosition().x << " - " << obstacle->getPosition().y << std::endl;
				mSceneLayers->at(Obstacle)->attachChild(std::move(obstacle));
			}
		}
	}
}
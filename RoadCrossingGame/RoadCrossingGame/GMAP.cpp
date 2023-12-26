#include "GMAP.h"
#include <iomanip>
#include "Others.h"

GMAP::GMAP(sf::RenderWindow& window, const float& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures, float* mScrollSpeed, bool* isLoss, Player* player)
	: mWindow(window)
	, mWorldBounds(0.f, yMapCoordinate, SCREEN_WIDTH, SCREEN_HEIGHT)
	, mRoadBounds(0.f, 0.f, window.getDefaultView().getSize().x, Constants::ROAD_SIZE)
	, mScrollSpeed(mScrollSpeed)
	, yCoor(yMapCoordinate)
	, isLoss(isLoss)
	, player(player)
{
	this->mSceneGraph = mSceneGraph;
	this->mSceneLayers = mSceneLayers;
	this->mTextures = mTextures;

	std::cout << this->mSceneLayers->size() << std::endl;
	buildScene();
	isInit = !isInit;
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
	checkLose(deltaTime);
}

void GMAP::checkLose(float deltaTime) {
	if (mAnimal.empty()) return;
	for (auto& it : mAnimal) {
		if (it->isIntersect(player->getBorder())) {
			//std::cout << "LOSE" << std::endl;
			//std::cout << "PLAYER: " << player->getBorder().left << " " << player->getBorder().top << " " << player->getBorder().left + player->getBorder().width << " " << player->getBorder().top + player->getBorder().height << std::endl;
			//std::cout << "Animal: " << it->getBorder().left << " " << it->getBorder().top << " " << it->getBorder().left + it->getBorder().width << " " << it->getBorder().top + it->getBorder().height << std::endl;
			*isLoss = true;
			return;
		}
	}
}

bool GMAP::isCollided(sf::FloatRect &border) {
	for (auto& it : mObstacle) {
		sf::FloatRect curRect = it->getRect();
		//std::cout << curRect.width << " " << curRect.height << std::endl;
		if (curRect.intersects(border)) {
			//std::cout << "PLAYER: " << border.left << " " << border.top << " " << border.left + border.width << " " << border.top + border.height << std::endl;
			//std::cout << "OBSTACLE: " << curRect.left << " " << curRect.top << " " << curRect.left + curRect.width << " " << curRect.top + curRect.height << std::endl;
			return true;
		}
	}

	//for (auto& it : mTrafficLight) {
	//	sf::FloatRect curRect = it->getRect();
	//	if (curRect.intersects(border)) return true;
	//}

	return false;
}

void GMAP::draw() {}

void GMAP::buildScene()
{
	generatePosition(isInit);
	//std::cout << "After generate position: " << std::endl;
	//std::cout << "Position:" << std::endl;
	//for (int i = 0; i < mapPos.size(); ++i) {
	//	std::cout << mapPos[i].first.x << " - " << mapPos[i].first.y;
	//	std::cout << ": " << mapPos[i].second << std::endl;
	//}
	generateRoads();
	generateObstacle(isInit);
	generateAnimals();
	generateTrafficLight();
}

void GMAP::generatePosition(bool isInit) {
	std::cout << "Get coordinate: " << mWorldBounds.left << " and " << getCoordinate().y << std::endl;
	int isRoad;
	if (isInit) {
		for (int i = mWorldBounds.top; i < getCoordinate().y + SCREEN_HEIGHT; i += ROAD_SIZE) {
			if (i >= getCoordinate().y + SCREEN_HEIGHT - 5 * ROAD_SIZE) {
				isRoad = 3;
			}
			else isRoad = randBiasedInt(0, 3, 0.4);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
	}
	else {
		for (int i = mWorldBounds.top; i < getCoordinate().y + SCREEN_HEIGHT; i += ROAD_SIZE) {
			isRoad = randBiasedInt(0, 3, 0.4);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
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

void GMAP::generateObstacle(bool isInit) {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 3) {
			int numOfObstacle;
			if (isInit) {
				numOfObstacle = randBiasedInt(4, 7, 0.8);
			}
			else numOfObstacle = randBiasedInt(4, Constants::maxObstacle, 0.4f);
			for (int j = 0; j < numOfObstacle; ++j) {
				int startPos = j * (mWorldBounds.width / numOfObstacle);
				int endPos = startPos + mWorldBounds.width / numOfObstacle;

				int type = randObject(0, Constants::maxObstacle, 0.7f);

				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
				mObstacle.push_back(obstacle.get());
				obstacle->setPosition(randInt(startPos, endPos), mapPos[i].first.y + 54);
				//std::cout << "Pos: " << obstacle->getPosition().x << " - " << obstacle->getPosition().y << std::endl;
				mSceneLayers->at(Obstacle)->attachChild(std::move(obstacle));
			}
		}
	}
}

void GMAP::generateAnimals() {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 1) {
			int type = randInt(0, 9);
			sf::Vector2f pos;
			if (type % 2 == 0) {
				pos = sf::Vector2f(mapPos[i].first.x - 400, mapPos[i].first.y - 50);
			}
			else {
				pos = sf::Vector2f(Constants::SCREEN_WIDTH - 400, mapPos[i].first.y - 50);
			}
			pos.y -= 10;
			for (int j = 0; j < maxAnimal; ++j) {
				std::unique_ptr<CANIMAL> animal(new CANIMAL(type, mWorldBounds, *mTextures, 50, 0.1));
				mAnimal.push_back(animal.get());
				pos.x = pos.x + randInt(150, 300);
				animal->setPosition(pos);
				animal->saveOrgPos(pos);
				mSceneLayers->at(Animal)->attachChild(std::move(animal));
				//std::cout << pos.x << " " << pos.y << std::endl;
			}
		}
	}
}

void GMAP::generateTrafficLight() {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 0 || mapPos[i].second == 2) {
			int hasTrafficLight = randBiasedInt(0, 1, 0.7f);
			if (hasTrafficLight) {
				int randPos = randInt(20, SCREEN_WIDTH - 50);
				std::unique_ptr<COBJECT> trafficLight(new COBJECT(0, *mTextures, sf::Vector2f(randPos, mapPos[i].first.y + 5.f)));
				mTrafficLight.push_back(trafficLight.get());
				mSceneLayers->at(Obstacle)->attachChild(std::move(trafficLight));
			}
		}
	}
}

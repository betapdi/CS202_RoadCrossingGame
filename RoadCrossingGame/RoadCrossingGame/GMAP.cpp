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
	generateVehicles();
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
			for (int i = 0; i < Constants::maxAnimal; ++i) {
				std::unique_ptr<CANIMAL> animal(new CANIMAL(type, mWorldBounds, *mTextures, 50, 0.1));
				mAnimal.push_back(animal.get());
				pos.x = pos.x + randInt(150, 300);
				animal->setPosition(pos);
				animal->saveOrgPos(pos);
				mSceneLayers->at(Animal)->attachChild(std::move(animal));
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

void GMAP::generateVehicles()
{
	generateCars();
	generateTrain();
}

void GMAP::generateCars()
{
	srand(time(0));
	int type = randEvenOdd(0, 7, false);
	//float speed;
	for (int i = 0; i < mapPos.size(); i++) {
		if (mapPos[i].second == 0) {
			//int type = randInt(0, 7);
			//sf::Vector2f position(Constants::SCREEN_WIDTH, mapPos[i].first.y);
			sf::Vector2f position;
			if (type % 2 != 0) {
				position = sf::Vector2f(mapPos[i].first.x - 100.f, mapPos[i].first.y);
				//type = randEvenOdd(0, 7, false);
				std::cout << type << " Pos: " << mapPos[i].first.x << std::endl;
			}
			else {
				position = sf::Vector2f(Constants::SCREEN_WIDTH - 400.f, mapPos[i].first.y);
				//type = randEvenOdd(0, 7, true);
				std::cout << type << " Pos: " << mapPos[i].first.x << std::endl;

			}
			//position.y -= 10;
			//speed = static_cast<float>(rand() % 50 + 150);
			position.y -= randInt(18, 20);
			//sf::Vector2f position(Constants::SCREEN_WIDTH, mapPos[i].first.y);
			for (int i = 0; i < Constants::maxCar; ++i) {
				if (type % 2 == 0) {
					type = randEvenOdd(0, 7, false);
				}
				else {
					type = randEvenOdd(0, 7, true);

				}
				//float speed = static_cast<float>(rand() % 200 + 200);
				std::unique_ptr<CVEHICLE> vehicle(new CVEHICLE(type, mWorldBounds, *mTextures, 200, 0.1));
				mVehicle.push_back(vehicle.get());
				/*if (type % 2 == 0) {
					position.x = position.x + randInt(250, 500);
				}
				else {
					position.x = position.x + randInt(50, 100);

				}*/
				position.x = position.x + randInt(150, 300);
				vehicle->setPosition(position);
				vehicle->saveOrgPos(position);
				mSceneLayers->at(Vehicle)->attachChild(std::move(vehicle));
			}
			if (type % 2 == 0) {
				type = randEvenOdd(0, 7, true);
			}
			else {
				type = randEvenOdd(0, 7, false);

			}
		}

	}
}

void GMAP::generateTrain()
{
	//int type1;
	for (int i = 0; i < mapPos.size(); i++) {
		if (mapPos[i].second == 2) {
			int type = randInt(8, 9);
			int type1 = 0;
			if (type == 8) {
				type1 = 10;
			}
			else if (type == 9) {
				type1 = 11;
			}
			sf::Vector2f pos;
			/*if (type % 2 != 0) {
				pos = sf::Vector2f(mapPos[i].first.x - 400, mapPos[i].first.y);
			}
			else {
				pos = sf::Vector2f(Constants::SCREEN_WIDTH - 400, mapPos[i].first.y);
			}*/
			if (type % 2 != 0) {
				pos = sf::Vector2f(mapPos[i].first.x - 1000, mapPos[i].first.y - 50);
			}
			else {
				pos = sf::Vector2f(Constants::SCREEN_WIDTH - 400, mapPos[i].first.y - 50);
			}
			pos.y -= 50;
			float headSize = 0;
			float tailSize = 0;
			for (int i = 0; i < Constants::maxTrain; i++) {
				std::unique_ptr<CVEHICLE> train(new CVEHICLE(type, mWorldBounds, *mTextures, 450, 0.1));
				mTrain.push_back(train.get());
				pos.x = pos.x + randInt(1000, 1500) + headSize + (tailSize * 5);
				train->setPosition(pos);
				train->saveOrgPos(pos);
				//float headSize;
				headSize = train->getBound().width;
				if (type % 2 == 0) pos.x += headSize - 45;
				else pos.x -= (headSize + 60);
				//mSceneLayers->at(Vehicle)->attachChild(std::move(train));
				for (int i = 0; i < 5; i++) {
					std::unique_ptr<CVEHICLE> train_tail(new CVEHICLE(type1, mWorldBounds, *mTextures, 450, 0.1));
					tailSize = train_tail->getBound().width;
					if (i > 0) {
						if (type % 2 == 0) {
							pos.x += (tailSize - 50);
						}
						else {
							pos.x -= (tailSize - 50);
						}
					}
					pos.y += 9;
					train_tail->setPosition(pos);
					train_tail->saveOrgPos(pos);

					/*if (type1 % 2 == 0) {
						pos.x += train_tail->getBound().width;
					}
					else {
						pos.x -= train_tail->getBound().width;

					}*/
					//pos.y -= 40;
					mTrainTail.push_back(train_tail.get());
					mSceneLayers->at(Vehicle)->attachChild(std::move(train_tail));
					pos.y -= 9;
				}

				mSceneLayers->at(Vehicle)->attachChild(std::move(train));
				//pos.x += train_tail->getBound().width;
			}
		}
	}
}
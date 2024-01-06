#include "GMAP.h"
#include <iomanip>
#include "Others.h"

GMAP::GMAP(sf::RenderWindow& window, const float& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures, float* mScrollSpeed, bool* isLoss, bool* isInit, Player* player)
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
	buildScene(isInit);
}

sf::Vector2f GMAP::getCoordinate() {
	return sf::Vector2f(mWorldBounds.left, mWorldBounds.top);
}

void GMAP::rebuild(const float& lastYCoordinate, bool isInit) {
	mWorldBounds.top = lastYCoordinate - SCREEN_HEIGHT;
	for (std::size_t i = 0; i < LayerCount - 1; ++i) {
		mSceneLayers->at(i)->clear();
	}

	mAnimal.clear();
	mTrafficLight.clear();
	mObstacle.clear();
	mMoney.clear();
	mapPos.clear();

	buildScene(isInit);
}

void GMAP::handleTouchBorder(Aircraft* mPlayerAircraft) {

}

void GMAP::update(float deltaTime)
{
	mSceneGraph->update(deltaTime);
	checkMoney();
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

void GMAP::checkMoney() {
	//if (mMoney.empty()) return;
	//for (auto it = mMoney.begin(); it != mMoney.end(); it++) {
	//	if ((*it)->isIntersect(player->getBorder())) {
	//		(*it)->setCollected(true);
	//		return;
	//	}
	//}
	if (mMoney.empty()) return;

	for (auto it = mMoney.begin(); it != mMoney.end();) {
		if ((*it)->isIntersect(player->getBorder())) {
			(*it)->setCollected(true);
			Constants::MONEY_COLLECTED->play();
			return;
			//it = mMoney.erase(it);  // Use the returned iterator after erasing
		}
		else {
			++it;
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

void GMAP::buildScene(bool isInit)
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
	generateMoney();
}


void GMAP::generatePosition(bool isInit) {
	//std::cout << "Get coordinate: " << mWorldBounds.left << " and " << getCoordinate().y << std::endl;
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
	if (isInit) {
		generateInitialObstacle();
	}
	else {
		for (int i = 0; i < mapPos.size(); ++i) {
			if (mapPos[i].second == 3) {
				int numOfObstacle;
				numOfObstacle = randBiasedInt(4, Constants::maxObstacle, 0.4f);
				float startPos = 0;
				float endPos = startPos + 120;
				for (int j = 0; j < numOfObstacle; ++j) {
					int type = randObject(0, Constants::maxObstacle, 0.7f);
					std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
					obstacle->setPosition(randInt(startPos, endPos), mapPos[i].first.y + 54);

					startPos = obstacle->getPosition().x + obstacle->getSizeX();
					endPos = startPos + mWorldBounds.width / numOfObstacle;

					mObstacle.push_back(obstacle.get());
					mSceneLayers->at(Obstacle)->attachChild(std::move(obstacle));
				}
			}
		}
	}
}

void GMAP::generateInitialObstacle() {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 3) {
			int numOfObstacle = randBiasedInt(10, 15, 0.5f);
			float startPos1 = 0;
			float endPos1 = startPos1 + 120;
			for (int j = 0; j < numOfObstacle; ++j) {
				int type = randObject(0, Constants::maxObstacle, 0.7f);
				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
				obstacle->setPosition(randInt(startPos1, endPos1), mapPos[i].first.y + 54.0f);
				startPos1 = obstacle->getPosition().x + 120;
				endPos1 = startPos1 + mWorldBounds.width / numOfObstacle;
				if ((startPos1 >= Constants::SCREEN_WIDTH / 2 - 100 && startPos1 < Constants::SCREEN_WIDTH / 2 + 50) ||
					(endPos1 >= Constants::SCREEN_WIDTH / 2 - 100 && endPos1 < Constants::SCREEN_WIDTH / 2 + 50)) {
					startPos1 = Constants::SCREEN_WIDTH / 2 + 70;
					endPos1 = startPos1 + mWorldBounds.width / numOfObstacle;
				}
				mObstacle.push_back(obstacle.get());
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
				pos = sf::Vector2f(Constants::SCREEN_WIDTH, mapPos[i].first.y - 10);
			}
			else {
				pos = sf::Vector2f(10, mapPos[i].first.y - 10);
			}
			if (type == 4 || type == 5) {
				pos.y -= 12;
			}
			for (int j = 0; j < maxAnimal; ++j) {
				std::unique_ptr<CANIMAL> animal(new CANIMAL(type, mWorldBounds, *mTextures, 50, 0.1));
				mAnimal.push_back(animal.get());
				if (type % 2 == 0) {
					pos.x = pos.x - randInt(200, 400);
				}
				else {
					pos.x = pos.x + randInt(200, 400);
				}
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

void GMAP::generateMoney() {
	for (int i = mapPos.size() - 1; i >= 0; --i) {
		int hasMoney = randBiasedInt(0, 1, 0.8f);
		sf::Vector2f pos;
		if (hasMoney) {
			int randPos = randInt(80, SCREEN_WIDTH - 50);
			std::unique_ptr<CMONEY> money(new CMONEY(*mTextures, 0.05f));
			pos = sf::Vector2f(randPos, mapPos[i].first.y);
			money->setPosition(pos);
			money->savePos(pos);
			mMoney.push_back(money.get());
			mSceneLayers->at(Money)->attachChild(std::move(money));
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
				position = sf::Vector2f(mapPos[i].first.x - 5000.f, mapPos[i].first.y);
				//type = randEvenOdd(0, 7, false);
				std::cout << type << " Pos: " << mapPos[i].first.x << std::endl;
			}
			else {
				position = sf::Vector2f(Constants::SCREEN_WIDTH - 100.f, mapPos[i].first.y);
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
				position.x = position.x + randInt(200, 1000);
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

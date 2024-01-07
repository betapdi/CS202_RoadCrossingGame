#include "GMAP.h"
#include <iomanip>
#include "Others.h"

GMAP::GMAP(sf::RenderWindow& window, const float& yMapCoordinate, std::vector<CSCENENODE*>* mSceneLayers, CSCENENODE* mSceneGraph, TextureHolder* mTextures, float* mScrollSpeed, bool* isLoss, bool* isInit, Player* player, int* score)
	: mWindow(window)
	, mWorldBounds(0.f, yMapCoordinate, SCREEN_WIDTH, SCREEN_HEIGHT)
	, mRoadBounds(0.f, 0.f, window.getDefaultView().getSize().x, Constants::ROAD_SIZE)
	, mScrollSpeed(mScrollSpeed)
	, yCoor(yMapCoordinate)
	, isLoss(isLoss)
	, player(player)
	, hasSFX(true)
	, score(score)
{
	this->mSceneGraph = mSceneGraph;
	this->mSceneLayers = mSceneLayers;
	this->mTextures = mTextures;

	//std::cout << this->mSceneLayers->size() << std::endl;
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
	mVehicle.clear();
	mTrain.clear();
	mTrainTail.clear();

	buildScene(isInit);
}

void GMAP::handleTouchBorder(Aircraft* mPlayerAircraft) {

}

void GMAP::update(float deltaTime)
{
	mSceneGraph->update(deltaTime);
	handleTrafficLightChange();
	checkMoney();
	checkLose(deltaTime);
}

void GMAP::handleTrafficLightChange() {
	int i = 0;
	while (!mTrafficLight.empty() && i < mTrafficLight.size()) {
		auto& it = mTrafficLight[i];
		float roadYPos = it->getPosition().y - 5.f;
		//std::cout << "WTF??? " << roadYPos << std::endl;

		for (int j = 0; j < mVehicle.size(); ++j) {
			auto& it1 = mVehicle[j];
			if (abs(roadYPos - (it1->getPosition().y + 20)) <= 20) {
				//std::cout << it1->getPosition().y << std::endl;
				int status = it->getStatus();

				if (status == 1) { //Red
					it1->setSpeed(0);
				}

				else if (status == 2) { //Yellow
					it1->setSpeed(100);
				}

				else it1->setSpeed(200);//Green
;			}
		}

		++i;
	}
}

void GMAP::checkLose(float deltaTime) {
	for (auto& it : mAnimal) {
		if (it->isIntersect(player->getBorder())) {
			*isLoss = true;
			return;
		}
	}

	for (auto& it : mVehicle) {
		if (it->isIntersect(player->getBorder())) {
			*isLoss = true;
			return;
		}
	}

	for (auto& it : mTrain) {
		if (it->isIntersect(player->getBorder())) {
			*isLoss = true;
			return;
		}
	}

	for (auto& it : mTrainTail) {
		if (it->isIntersect(player->getBorder())) {
			*isLoss = true;
			return;
		}
	}
}

void GMAP::checkMoney() {
	if (mMoney.empty()) return;

	for (auto it = mMoney.begin(); it != mMoney.end();) {
		if ((*it)->isIntersect(player->getBorder())&& !(*it)->isCollect()) {
			(*it)->setCollected(true);
			if (hasSFX) {
				Constants::MONEY_COLLECTED->play();
			}
			it = mMoney.erase(it);  // Use the returned iterator after erasing
			(*score)+=10;
			return;
		}
		else {
			++it;
		}

	}
}

void GMAP::setSFXAllow(bool isAllowed) {
	hasSFX = isAllowed;
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
	generateAnimals();
	generateVehicles();
	generateObstacle(isInit);
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
				float endPos = startPos + mWorldBounds.width / numOfObstacle;
				for (int j = 0; j < numOfObstacle; ++j) {
					int type = randObject(0, Constants::maxObstacle, 0.7f);
					std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
					sf::Vector2f pos(randInt(startPos, endPos), mapPos[i].first.y + 54);
					obstacle->setPosition(pos);
					obstacle->savePos(pos);
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
			int numOfObstacle = randBiasedInt(4, 10, 0.5f);
			float startPos1 = 0;
			float endPos1 = startPos1 + 120;
			for (int j = 0; j < numOfObstacle; ++j) {
				int type = randObject(0, Constants::maxObstacle, 0.7f);
				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
				sf::Vector2f pos(randInt(startPos1, endPos1), mapPos[i].first.y + 54.0f);
				obstacle->setPosition(pos);
				obstacle->savePos(pos);
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
				std::unique_ptr<CANIMAL> animal(new CANIMAL(type, *mTextures, 50, 0.1));
				if (type % 2 == 0) {
					pos.x = pos.x - randInt(200, 400);
				}
				else {
					pos.x = pos.x + randInt(200, 400);
				}
				animal->setPosition(pos);
				animal->saveOrgPos(pos);
				mAnimal.push_back(animal.get());
				mSceneLayers->at(Animal)->attachChild(std::move(animal));
				//std::cout << pos.x << " " << pos.y << std::endl;
			}
		}
	}
}



void GMAP::generateTrafficLight() {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 0) {
			int hasTrafficLight = randBiasedInt(0, 1, 0.7f);
			if (hasTrafficLight) {
				int randPos = randInt(50, SCREEN_WIDTH - 50);
				std::unique_ptr<COBJECT> trafficLight(new COBJECT(0, *mTextures, sf::Vector2f(randPos, mapPos[i].first.y + 5.f)));
				//std::cout << "GEN TRAFFIC: " << trafficLight->getPosition().y << std::endl;
				mTrafficLight.push_back(trafficLight.get());
				mSceneLayers->at(TrafficLight)->attachChild(std::move(trafficLight));
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
				//std::cout << type << " Pos: " << mapPos[i].first.x << std::endl;
			}
			else {
				position = sf::Vector2f(Constants::SCREEN_WIDTH - 100.f, mapPos[i].first.y);
				//type = randEvenOdd(0, 7, true);
				//std::cout << type << " Pos: " << mapPos[i].first.x << std::endl;

			}
			//position.y -= 10;
			//speed = static_cast<float>(rand() % 50 + 150);
			position.y -= 20;
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

				//std::cout << "GEN CARS: " << vehicle->getPosition().y << std::endl;
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
				std::unique_ptr<CVEHICLE> train(new CVEHICLE(type, mWorldBounds, *mTextures, 700, 0.1));
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
					std::unique_ptr<CVEHICLE> train_tail(new CVEHICLE(type1, mWorldBounds, *mTextures, 700, 0.1));
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

void GMAP::savePos(std::ofstream& fout) {
	//fout("../Data/savegame.dat", std::ios::binary | std::ios::out);

	if (fout.is_open()) {
		std::size_t mapPosSize = mapPos.size();
		fout.write((char*)(&mapPosSize), sizeof(std::size_t));

		for (const auto& it : mapPos) {
			fout.write((char*)(&it.first), sizeof(sf::Vector2f));
			fout.write((char*)(&it.second), sizeof(int));
		}

		std::size_t numObstacles = mObstacle.size();
		fout.write((char*)(&numObstacles), sizeof(std::size_t));

		for (const auto& obstacle : mObstacle) {
			obstacle->save(fout);
		}
		fout.close();
	}
	else {
		std::cerr << "Unable to open savegame.dat" << std::endl;
	}
}

void GMAP::loadPos(std::ifstream& fin) {
	std::size_t mapPosSize = mapPos.size();
	fin.read((char*)(&mapPosSize), sizeof(std::size_t));
	mapPos.clear();
	mObstacle.clear();
	//Read position from file
	for (std::size_t i = 0; i < mapPosSize; ++i) {
		sf::Vector2f pos;
		int roadType;
		fin.read((char*)(&pos), sizeof(sf::Vector2f));
		fin.read((char*)(&roadType), sizeof(int));

		mapPos.push_back(std::make_pair(pos, roadType));
	}
	//Generate road
	generateRoads();

	//Generate obstacles form file
	std::size_t numObstacles;
	fin.read((char*)(&numObstacles), sizeof(std::size_t));

	for (std::size_t i = 0; i < numObstacles; ++i) {
		int type;
		sf::Vector2f pos;
		fin.read((char*)(&type), sizeof(int));
		fin.read((char*)(&pos), sizeof(sf::Vector2f));
		std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, *mTextures));
		obstacle->setPosition(pos);
		mObstacle.push_back(obstacle.get());
		mSceneLayers->at(Obstacle)->attachChild(std::move(obstacle));
	}
}

void GMAP::saveCharacterID(std::ofstream& fout) {

}
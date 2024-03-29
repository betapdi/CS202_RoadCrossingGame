#include "GWORLD.h"
#include <numeric>
#include "GSTATE.h"

GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mScrollSpeed(-60.f)
	, mPlayerAircraft(nullptr)
	, isLoss(false)
	, moveWorld(false)
	, playSFX(true)
	, isInit(true)
	, isBackFromPause(false)
{
	//mWindow.setView(sf::View(sf::FloatRect(0, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT)));
	//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
	mSpawnPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	loadTextures();
	buildPlayer();
	buildMaps();
	//snow.init();
}

void GWORLD::processEvents(sf::Event &event) {
	player.process(event);
	//switch (event.type) {
	//case sf::Event::KeyPressed:
	//	if (event.key.code == sf::Keyboard::Space) {
	//		hasSnow = !hasSnow;
	//	}
	//	break;
	//}
}

GMAP* GWORLD::getCurrentMap() {
	return &mMaps[id.front()];
}

void GWORLD::update(float deltaTime) {
	//scroll the view
	if (score > 30) {
		mScrollSpeed = -70.0f;
	}
	else if (score > 60) {
		mScrollSpeed = -80.0f;
	}
	else if (score > 100) {
		mScrollSpeed = -100.0f;
	}
	if (!isLoss) {
		if (moveWorld) mWorldView.move(0.f, mScrollSpeed * deltaTime);
	}

	//if (hasSnow) {
	//	snow.update(deltaTime);
	//}

	if (isBackFromPause || isInit) {
		std::vector<bool> setting = getSetting();
		player.setTexture(setting[0]);
		if (!setting[1]) {
			Constants::ROUND_N_ROUND->stop();
		}
		playSFX = setting[2];
		setBackFromPause(false);
		isInit = false;
	}

	playerMovement(deltaTime);

	//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;

	//std::cout << "Player position: " << mPlayerAircraft->getPosition().x << ", " << mPlayerAircraft->getPosition().y << std::endl;
	//Handle map out of world
	handleMapOutOfWorld(deltaTime);

	//Handle player out of world
	handlePlayerOutOfWorld(deltaTime);

	calculateScore();

	//Handle player touches border
	GMAP* currMap = getCurrentMap();

	// Apply movements && Scroll the world downward
	for (auto& it : mMaps) {
		it.setSFXAllow(playSFX);
		it.update(deltaTime);
	}

	if (isLoss) {
		//std::cout << player.getBorder().left << " " << player.getBorder().top << std::endl;
		if (playSFX) {
			Constants::GAME_OVER_SFX->setVolume(40);
			Constants::GAME_OVER_SFX->play();
		}

		if (player.explosion(deltaTime)) {
			std::ofstream fout;
			fout.open("../Data/Ranking.txt", std::ofstream::app);
			fout << score << "\n";
			fout.close();
			STATEMACHINE::getInstance()->changeState(GAMEOVER, 0);
		}
	}
}

void GWORLD::handlePlayerOutOfWorld(float deltaTime) {
	float viewYCoordinate = mWorldView.getCenter().y + mWorldView.getSize().y / 2.0f;

	//std::cout << "Current View: " << viewYCoordinate << std::endl;
	//std::cout << "Current Player: " << player.getBorder().left << " " << player.getBorder().top << " " << player.getBorder().height << std::endl;

	if (viewYCoordinate < player.getBorder().top + player.getBorder().height - 1) {
		//std::cout << "GAME OVER because Player out of World!!" << std::endl;
		//std::cout << "ViewYCoordinate: " << viewYCoordinate << std::endl;
		//std::cout << "PlayerYPos: " << player.getBorder().top + player.getBorder().height << std::endl;
		isLoss = true;
		return;
	}
}

void GWORLD::handleMapOutOfWorld(float deltaTime) {
	GMAP* currMap = getCurrentMap();
	sf::Vector2f viewCenter = mWorldView.getCenter();
	float viewYCoordinate = mWorldView.getCenter().y + mWorldView.getSize().y / 2.0f;
	float lastYCoordinate = mMaps[id.back()].getCoordinate().y;

	//std::cout << viewYCoordinate << std::endl;

	//out of world
	if (viewYCoordinate < currMap->getCoordinate().y) {
		//std::cout << id.front() << std::endl;
		GMAP* currMap = getCurrentMap();
		currMap->rebuild(lastYCoordinate, isInit);
		std::rotate(id.begin(), id.begin() + 1, id.end());
	}
}

void GWORLD::getPlayerID() {
	std::ifstream fin;
	fin.open("../Data/Setting.txt");
	if (!fin.is_open()) {
		std::cout << "Unable to open Setting File.\n";
		return;
	}
	fin >> playerID;
	fin.close();
}

void GWORLD::buildPlayer() {
	// Initialize the different layers
	for (std::size_t currMap = 0; currMap < 3; ++currMap) {
		for (std::size_t i = 0; i < LayerCount; ++i) {
			CSCENENODE::Ptr layer(new CSCENENODE());
			worldSceneLayers[currMap].push_back(layer.get());
			worldSceneGraph[currMap].attachChild(std::move(layer));
		}
	}

	getPlayerID();
	player.ini(playerID);

}

void GWORLD::buildMaps() {
	id.resize(3); std::iota(id.begin(), id.end(), 0);

	for (int i = 0; i < 3; ++i) {
		mMaps.push_back(GMAP(mWindow, (float)Constants::SCREEN_HEIGHT * (-i), &worldSceneLayers[i], &worldSceneGraph[i], &mTextures, &mScrollSpeed, &isLoss, &isInit, &player, &score));
		//std::cout << SCREEN_HEIGHT * (-i) << std::endl;
	}
}

void GWORLD::draw() {
	//if (isLoss) return;
	mWindow.clear(sf::Color::White);

	mWindow.setView(mWorldView);

	for (std::size_t i = 0; i < LayerCount; ++i) {
		for (std::size_t currMap = 0; currMap < 3; ++currMap) {
			mWindow.draw(*worldSceneLayers[currMap][i]);
		}
	}

	player.render(&mWindow);
	//if (hasSnow) {
	//	snow.render(&mWindow);
	//}
}

void GWORLD::playerMovement(float deltaTime)
{
	if (!isCollided(player._sprite, deltaTime)) player._sprite.move(player.velocity.x * deltaTime, player.velocity.y * deltaTime);

	switch (player.dir) {
	case sf::Keyboard::Up:
		player.curTime += deltaTime;
		if (player.curTime >= deltaTime * 4) {
			if (player.source.y != DIRECTION_Y_UP_INITAL) {
				player.source.x = DIRECTION_X_UP_INITAL;
				player.source.y = DIRECTION_Y_UP_INITAL;
			}
			if (player.source.x >= 2)
				player.source.x = DIRECTION_X_UP_INITAL;
			else player.source.x++;
			player.curTime -= deltaTime * 4;
		}
		break;
	case sf::Keyboard::Down:
		player.curTime += deltaTime;
		if (player.curTime >= deltaTime * 4) {
			if (player.source.y != DIRECTION_Y_DOWN_INITAL) {
				player.source.x = DIRECTION_X_DOWN_INITAL;
				player.source.y = DIRECTION_Y_DOWN_INITAL;
			}
			if (player.source.x >= 2)
				player.source.x = DIRECTION_X_DOWN_INITAL;
			else player.source.x++;
			player.curTime -= deltaTime * 4;
		}
		break;
	case sf::Keyboard::Right:
		player.curTime += deltaTime;
		if (player.curTime >= deltaTime * 4) {
			if (player.source.y != DIRECTION_Y_RIGHT_INITAL) {
				player.source.x = DIRECTION_X_RIGHT_INITAL;
				player.source.y = DIRECTION_Y_RIGHT_INITAL;
			}
			if (player.source.x >= 2)
				player.source.x = DIRECTION_X_RIGHT_INITAL;
			else player.source.x++;
			player.curTime -= deltaTime * 4;
		}
		break;
	case sf::Keyboard::Left:
		player.curTime += deltaTime;
		if (player.curTime >= deltaTime * 4) {
			if (player.source.y != DIRETION_Y_LEFT_INITAL) {
				player.source.x = DIRECTION_X_LEFT_INITAL;
				player.source.y = DIRETION_Y_LEFT_INITAL;
			}
			if (player.source.x >= 2)
				player.source.x = DIRECTION_X_LEFT_INITAL;
			else player.source.x++;
			player.curTime -= deltaTime * 4;
		}
		break;
	}
}

bool GWORLD::isCollided(sf::Sprite& sprite, const float& deltaTime) {
	sf::Vector2f getPos = sprite.getPosition() + player.velocity * deltaTime;
	getPos.y -= SPRITE_HEIGHT / 2.0f;
	//sf::FloatRect nextPosBorder = { getPos + player.velocity * deltaTime, sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT) };
	sf::FloatRect nextPosBorder = { getPos, sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT) };

	//Out of map (left, right)
	if (nextPosBorder.left < 0 || nextPosBorder.left + nextPosBorder.width > SCREEN_WIDTH) return true;

	//Out of view (top)
	if (nextPosBorder.top < mWorldView.getCenter().y - mWorldView.getSize().y / 2.0f) return true;

	//Collide with obstacle
	for (auto& it : mMaps) {
		if (it.isCollided(nextPosBorder)) return true;
	}

	return false;
}

void GWORLD::calculateScore() {
	if (player._sprite.getPosition().y < scorey) {
		score++;
		scorey -= 60;
	}
}

void GWORLD::setMoveWorld(bool moveWorld) {
	this->moveWorld = moveWorld;
}

void GWORLD::setBackFromPause(bool isBack) {
	isBackFromPause = isBack;
}

//void GWORLD::setSnow(bool hasSnow) {
//	this->hasSnow = hasSnow;
//}

float GWORLD::getScrollSpeed() {
	return mScrollSpeed;
}


void GWORLD::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");

	// --- ROAD TEXTURES ---
	//mTextures.load(Textures::DEFAULT_ROAD,			"Media/Textures/default_road_resize.png");
	mTextures.load(Textures::DEFAULT_ROAD,			"Media/Textures/default_street_edit.png");
	//mTextures.load(Textures::DEFAULT_ROAD,		"Media/Textures/streettile.png");
	mTextures.load(Textures::DOTTED_ROAD,			"Media/Textures/white_dotted_road_resize.png");
	mTextures.load(Textures::RAIL_ROAD,				"Media/Textures/railroad_tile.png");
	mTextures.load(Textures::GROUND,				"Media/Textures/ground.png");
	mTextures.load(Textures::WATER,					"Media/Textures/water.png");


	// --- PAVEMET TEXTURES ---
	//mTextures.load(Textures::PAVEMENT,				"Media/Textures/pavement.png");
	mTextures.load(Textures::PAVEMENT,				"Media/Textures/pavement_edit.png");

	// --- OBSTACLES ---
	mTextures.load(Textures::SMALL_TREE,			"Media/Textures/small_tree.png");
	mTextures.load(Textures::BIG_TREE,				"Media/Textures/double_tree.png");
	mTextures.load(Textures::BENCH,					"Media/Textures/bench.png");
	//mTextures.load(Textures::GRASS,				"Media/Textures/grass.png");
	mTextures.load(Textures::VENDING_MACHINE,		"Media/Textures/vending_machine.png");
	mTextures.load(Textures::BLUE_SIGN,				"Media/Textures/blue_sign.png");
	mTextures.load(Textures::GREEN_SIGN,			"Media/Textures/green_sign.png");
	mTextures.load(Textures::WHITE_SIGN,			"Media/Textures/white_sign.png");
	mTextures.load(Textures::HOTDOG,				"Media/Textures/triple_tree.png");
	mTextures.load(Textures::LIGHT,					"Media/Textures/light.png");
	mTextures.load(Textures::GROCERY,				"Media/Textures/grocery.png");
	mTextures.load(Textures::SHOP,					"Media/Textures/shop_1.png");
	mTextures.load(Textures::HOUSE,					"Media/Textures/house.png");
	//mTextures.load(Textures::TRAFFIC_LIGHT,		"Media/Textures/traffic_light.png");
	mTextures.load(Textures::TRAFFIC_LIGHT,			"Media/Textures/traffic_light_edit.png");
	mTextures.load(Textures::MONEY,					"Media/Textures/coin.png");

	// --- ANIMALS ---
	mTextures.load(Textures::BEAR_LEFT,				"Media/Textures/bear_left.png");
	mTextures.load(Textures::BEAR_RIGHT,			"Media/Textures/bear_right.png");
	mTextures.load(Textures::DEER_L,				"Media/Textures/deer_left.png");
	mTextures.load(Textures::DEER_R,				"Media/Textures/deer_right.png");
	mTextures.load(Textures::REINDEER_L,			"Media/Textures/reindeer_left.png");
	mTextures.load(Textures::REINDEER_R,			"Media/Textures/reindeer_right.png");
	mTextures.load(Textures::FOX_L,					"Media/Textures/fox_left.png");
	mTextures.load(Textures::FOX_R,					"Media/Textures/fox_right.png");
	mTextures.load(Textures::WOLF_L,				"Media/Textures/wolf_left.png");
	mTextures.load(Textures::WOLF_R,				"Media/Textures/wolf_right.png");

	// --- VEHICLES ---
	mTextures.load(Textures::BLUE_CAR_L, "Media/Textures/vehicles/blue_car_left.png");
	mTextures.load(Textures::BLUE_CAR_R, "Media/Textures/vehicles/blue_car_right.png");
	mTextures.load(Textures::GREEN_CAR_L, "Media/Textures/vehicles/green_car_left.png");
	mTextures.load(Textures::GREEN_CAR_R, "Media/Textures/vehicles/green_car_right.png");	
	mTextures.load(Textures::POLICE_CAR_L, "Media/Textures/vehicles/police_car_left.png");
	mTextures.load(Textures::POLICE_CAR_R, "Media/Textures/vehicles/police_car_right.png");
	//mTextures.load(Textures::ORANGE_CAR_L, "Media/Textures/vehicles/orange_car_left.png");
	//mTextures.load(Textures::ORANGE_CAR_R, "Media/Textures/vehicles/orange_car_right.png");
	mTextures.load(Textures::RED_CAR_L, "Media/Textures/vehicles/red_car_left.png");
	mTextures.load(Textures::RED_CAR_R, "Media/Textures/vehicles/red_car_right.png");
	mTextures.load(Textures::TRUCK_L, "Media/Textures/vehicles/truck_left.png");
	mTextures.load(Textures::TRUCK_R, "Media/Textures/vehicles/truck_right.png");
	mTextures.load(Textures::BLUE_TRUCK_L, "Media/Textures/vehicles/blue_truck_left.png");
	mTextures.load(Textures::BLUE_TRUCK_R, "Media/Textures/vehicles/blue_truck_right.png");
	mTextures.load(Textures::OLD_TRAIN_L, "Media/Textures/vehicles/old_train_left.png");
	mTextures.load(Textures::OLD_TRAIN_R, "Media/Textures/vehicles/old_train_right.png");
	mTextures.load(Textures::TRAIN_L, "Media/Textures/vehicles/train_left.png");
	mTextures.load(Textures::TRAIN_R, "Media/Textures/vehicles/train_right.png");
}
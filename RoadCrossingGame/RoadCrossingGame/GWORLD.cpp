#include "GWORLD.h"
#include <numeric>

#include "Others.h"
GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2048.f)
	, mRoadBounds(0.f, 0.f, mWorldView.getSize().x, Constants::ROAD_SIZE)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(-50.f)
	, mScrollSpeed(-100.f)
	, mPlayerAircraft(nullptr)
{
	//mWindow.setView(sf::View(sf::FloatRect(0, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT)));
	//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
	mSpawnPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	isInit = true;
	loadTextures();
	buildPlayer();
	buildMaps();
}

GMAP* GWORLD::getCurrentMap() {
	return &mMaps[id.front()];
}

void GWORLD::update(float deltaTime) {
	//scroll the view
	mWorldView.move(0.f, mScrollSpeed * deltaTime);

	//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
		mWorldBounds.left = 0;
		mWorldBounds.top = 0;
		mWorldView.setCenter(mSpawnPosition);
	}

	//std::cout << "Player position: " << mPlayerAircraft->getPosition().x << ", " << mPlayerAircraft->getPosition().y << std::endl;
	//Handle map out of world
	handleMapOutOfWorld(deltaTime);

	//Handle player touches border
	GMAP* currMap = getCurrentMap();

	//Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (curView.y <= viewSize.y / 2) {
		// --> keep player position
		mWorldView.setCenter(mSpawnPosition);
		mPlayerAircraft->setPosition(position);
	}

	//If player touches borders, flip its X velocity
	if (position.x <= 150.f
		|| position.x >= SCREEN_WIDTH - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	// Apply movements && Scroll the world downward
	for (auto& it : mMaps) {
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
		currMap->rebuild(lastYCoordinate);
		std::rotate(id.begin(), id.begin() + 1, id.end());
	}
}
void GWORLD::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");

	// --- ROAD TEXTURES ---
	mTextures.load(Textures::DEFAULT_ROAD,		"Media/Textures/default_road_resize.png");
	mTextures.load(Textures::DOTTED_ROAD,		"Media/Textures/white_dotted_road.png");
	mTextures.load(Textures::RAIL_ROAD,			"Media/Textures/railroad_tile.png");


	// --- PAVEMET TEXTURES ---
	mTextures.load(Textures::PAVEMENT,			"Media/Textures/pavement.png");

	// --- OBSTACLES ---
	mTextures.load(Textures::FAST_FOOD_STORE,	"Media/Textures/fast_food_store.png");
	mTextures.load(Textures::COFFEE_SHOP,		"Media/Textures/coffee_shop.png");
	mTextures.load(Textures::GROCERY,			"Media/Textures/grocery.png");
	mTextures.load(Textures::SHOP,				"Media/Textures/shop_1.png");
	mTextures.load(Textures::BARBER_SHOP,		"Media/Textures/barber_shop.png");
	mTextures.load(Textures::BREAD_SHOP,		"Media/Textures/bread_shop.png");
	mTextures.load(Textures::VEGETABLE_SHOP,	"Media/Textures/vegetable_shop.png");
	mTextures.load(Textures::HOUSE,				"Media/Textures/house.png");
	mTextures.load(Textures::BLUE_SIGN,			"Media/Textures/blue_sign.png");
	mTextures.load(Textures::GREEN_SIGN,		"Media/Textures/green_sign.png");
	mTextures.load(Textures::WHITE_SIGN,		"Media/Textures/hotdog.png");
	mTextures.load(Textures::VENDING_MACHINE,	"Media/Textures/vending_machine.png");
	mTextures.load(Textures::GRASS,				"Media/Textures/grass.png");
}
	mTextures.load(Textures::DOTTED_ROAD, "Media/Textures/white_dotted_road.png");
void GWORLD::buildPlayer() {
}

void GWORLD::buildScene()
{
	// Initialize the different layers
	for (std::size_t currMap = 0; currMap < 3; ++currMap) {
		for (std::size_t i = 0; i < LayerCount; ++i) {
			CSCENENODE::Ptr layer(new CSCENENODE());
			worldSceneLayers[currMap].push_back(layer.get());


	//	--- PLAYER ---
	// Add player's aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	worldSceneLayers[0][Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}

void GWORLD::buildMaps() {
	id.resize(3); std::iota(id.begin(), id.end(), 0);
	mPlayerAircraft->attachChild(std::move(rightEscort));	

	// --- ROAD ---
	generateRoads();
	//generateObstacle();
}

void GWORLD::generatePosition(bool isInit) {
	if (isInit) {
		for (int i = 0; i < 3; ++i) {
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - i * Constants::ROAD_SIZE),0));
		}
		for (int i = mWorldBounds.top + mWorldBounds.height - 3 * Constants::ROAD_SIZE; i >= mWorldBounds.top; i -= Constants::ROAD_SIZE) {
			int isRoad = randBiasedInt(0, 2, 0.1);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
		isInit = 0;
	}
	else {
		for (int i = mWorldBounds.top + mWorldBounds.height; i >= mWorldBounds.top; i -= Constants::ROAD_SIZE) {
			int isRoad = randBiasedInt(0, 2, 0.1);
			mapPos.push_back(std::pair<sf::Vector2f, int>(sf::Vector2f(mWorldBounds.left, i), isRoad));
		}
	}
}
	
	for (int i = 0; i < 3; ++i) {
		mMaps.push_back(GMAP(mWindow, (float)Constants::SCREEN_HEIGHT * (-i), &worldSceneLayers[i], &worldSceneGraph[i], &mTextures, &mScrollSpeed));
		//std::cout << SCREEN_HEIGHT * (-i) << std::endl;
	}
}
void GWORLD::generateRoads() {
	for (int i = 0; i < mapPos.size(); ++i) {
		sf::IntRect textureRect1(mRoadBounds);
		sf::Texture* mText = nullptr;
		if (mapPos[i].second == 1) {
			mText = &mTextures.get(Textures::DEFAULT_ROAD);
		}
		else if (mapPos[i].second == 2) {
			mText = &mTextures.get(Textures::RAIL_ROAD);
		}
		else {
			mText = &mTextures.get(Textures::PAVEMENT);
		}
		mText->setRepeated(true);
		if (mText) {
			std::unique_ptr<CROAD> road(new CROAD(*mText, textureRect1));
			road->setPosition(mapPos[i].first);
			mSceneLayers[Road]->attachChild(std::move(road));
		}
	}
}

void GWORLD::generateObstacle() {
	for (int i = 0; i < mapPos.size(); ++i) {
		if (mapPos[i].second == 0) {
			int numOfObstacle = randInt(0, Constants::maxObstacle);
			for (int j = 0; j < numOfObstacle; ++j) {
				int startPos = j * (mWorldBounds.width / numOfObstacle);
				int endPos = startPos + mWorldBounds.width / numOfObstacle;
				int type = randInt(0, COBSTACLE::GRASS);

				std::unique_ptr<COBSTACLE> obstacle(new COBSTACLE(type, mTextures));
				obstacle->setPosition(randInt(startPos, endPos), mapPos[i].first.y);
				//std::cout << "Pos: " << obstacle->getPosition().x << " - " << obstacle->getPosition().y << std::endl;
				mSceneLayers[Obstacle]->attachChild(std::move(obstacle));
			}
		}
	}
void GWORLD::draw() {
	mWindow.setView(mWorldView);

	for (std::size_t i = 0; i < LayerCount; ++i) {
		for (std::size_t currMap = 0; currMap < 3; ++currMap) {
			mWindow.draw(*worldSceneLayers[currMap][i]);
		}
	}
}

void GWORLD::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
	mTextures.load(Textures::DEFAULT_ROAD, "Media/Textures/default_road_resize.png");
	mTextures.load(Textures::DOTTED_ROAD, "Media/Textures/white_dotted_road.png");
	mTextures.load(Textures::PAVEMENT, "Media/Textures/pavement.png");
	//mTextures.load(Textures::DOTTED_ROAD, "Media/Textures/Objects.png");

void GWORLD::generateRoads() {
	//::vector<CROAD::Type> roadTypes = { CROAD::DEFAULT_ROAD,CROAD::DOTTED_ROAD };
	//mSceneLayers[Road]
}
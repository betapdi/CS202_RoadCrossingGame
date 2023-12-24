#include "GWORLD.h"
#include <numeric>

GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mScrollSpeed(-100.f)
	, mPlayerAircraft(nullptr)
{
	//mWindow.setView(sf::View(sf::FloatRect(0, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT)));
	//std::cout << "View position: " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
	mSpawnPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
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

	//std::cout << "Player position: " << mPlayerAircraft->getPosition().x << ", " << mPlayerAircraft->getPosition().y << std::endl;
	//Handle map out of world
	handleMapOutOfWorld(deltaTime);

	//Handle player touches border
	GMAP* currMap = getCurrentMap();

	//Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If player touches borders, flip its X velocity
	if (position.x <= 150.f
		|| position.x >= SCREEN_WIDTH - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	// Apply movements && Scroll the world downward
	for (auto& it : mMaps) {
		it.update(deltaTime);
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
		currMap->rebuild(lastYCoordinate);
		std::rotate(id.begin(), id.begin() + 1, id.end());
	}
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

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	worldSceneLayers[0][Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}

void GWORLD::buildMaps() {
	id.resize(3); std::iota(id.begin(), id.end(), 0);

	for (int i = 0; i < 3; ++i) {
		mMaps.push_back(GMAP(mWindow, (float)Constants::SCREEN_HEIGHT * (-i), &worldSceneLayers[i], &worldSceneGraph[i], &mTextures, &mScrollSpeed));
		//std::cout << SCREEN_HEIGHT * (-i) << std::endl;
	}
}

void GWORLD::draw() {
	//mWindow.setView(mWorldView);

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
	mTextures.load(Textures::BIG_TREE,				"Media/Textures/small_tree_resize.png");
	mTextures.load(Textures::BENCH,					"Media/Textures/bench.png");
	//mTextures.load(Textures::GRASS,				"Media/Textures/grass.png");
	mTextures.load(Textures::VENDING_MACHINE,		"Media/Textures/vending_machine.png");
	mTextures.load(Textures::BLUE_SIGN,				"Media/Textures/blue_sign.png");
	mTextures.load(Textures::GREEN_SIGN,			"Media/Textures/green_sign.png");
	mTextures.load(Textures::WHITE_SIGN,			"Media/Textures/white_sign.png");
	mTextures.load(Textures::HOTDOG,				"Media/Textures/hotdog.png");
	mTextures.load(Textures::LIGHT,					"Media/Textures/light.png");
	mTextures.load(Textures::GROCERY,				"Media/Textures/grocery.png");
	mTextures.load(Textures::SHOP,					"Media/Textures/shop_1.png");
	mTextures.load(Textures::HOUSE,					"Media/Textures/house.png");
	//mTextures.load(Textures::TRAFFIC_LIGHT,			"Media/Textures/traffic_light.png");
	mTextures.load(Textures::TRAFFIC_LIGHT,			"Media/Textures/traffic_light_edit.png");

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
}
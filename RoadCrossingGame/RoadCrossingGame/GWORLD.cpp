#include "GWORLD.h"
#include <numeric>

GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mTextures()
	, mSpawnPosition(mWindow.getDefaultView().getSize().x / 2.f, mWindow.getDefaultView().getSize().y / 2.f)
	, mScrollSpeed(100.f)
	, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildPlayer();
	buildMaps();
}

GMAP* GWORLD::getCurrentMap() {
	return &mMaps[id.front()];
}

void GWORLD::update(float deltaTime)
{
	//Handle map out of world
	handleMapOutOfWorld(deltaTime);

	//Get current map
	GMAP* currMap = getCurrentMap();

	//Handle player touches border
	currMap->handleTouchBorder(mPlayerAircraft);

	// Apply movements && Scroll the world downward
	for (auto& it : mMaps) {
		it.update(deltaTime);
	}
}

void GWORLD::handleMapOutOfWorld(float deltaTime) {
	GMAP* currMap = getCurrentMap();
	int yCoordinate = currMap->getCoordinate().y;
	int lastYCoordinate = currMap->getCoordinate().y;

	//out of world
	if (yCoordinate > (int)Constants::SCREEN_HEIGHT * 3) {
		std::rotate(id.begin(), id.begin() + 1, id.end());
		GMAP* currMap = getCurrentMap();
		currMap->rebuild(lastYCoordinate);
	}
}

void GWORLD::buildPlayer() {
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		CSCENENODE::Ptr layer(new CSCENENODE());
		mSceneLayers.push_back(layer.get());
		mSceneGraph.attachChild(std::move(layer));
	}

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

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
		mMaps.push_back(GMAP(mWindow, (int)Constants::SCREEN_HEIGHT * (2 - i), &mSceneLayers, &mSceneGraph, &mTextures));
	}
}

void GWORLD::draw() {
	mWindow.draw(mSceneGraph);
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
}
#include "GWORLD.h"

GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mTextures()
	, mSpawnPosition(mWindow.getDefaultView().getSize().x / 2.f, mWindow.getDefaultView().getSize().y / 2.f)
	, mScrollSpeed(100.f)
	, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildMaps();
}

void GWORLD::update(float deltaTime)
{
	//Handle map out of sight
	if (mMaps.front())

	//Get current map
	GMAP& currMap = mMaps.front();

	//Handle player touches border
	currMap.handleTouchBorder(mPlayerAircraft);

	// Apply movements && Scroll the world downward
	for (auto& it : mMaps) {
		it.update(deltaTime);
	}
}

void GWORLD::buildPlayer() {
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
	for (int i = 0; i < 3; ++i) {
		mMaps.push_front(GMAP(mWindow));
	}
}

void GWORLD::draw() {
	for (auto& it : mMaps) {
		it.draw();
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
}
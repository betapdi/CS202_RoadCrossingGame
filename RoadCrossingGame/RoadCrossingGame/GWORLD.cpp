#include "GWORLD.h"

GWORLD::GWORLD(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
	, mScrollSpeed(-100.f)
	, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildMaps();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void GWORLD::update(float deltaTime)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * deltaTime); //view keo len tren

	if (mWorldView.getCenter().y - mWorldView.getSize().y / 2.f > mWorldBounds.top + mWorldBounds.height)
	{
		mWorldBounds.left = 0;
		mWorldBounds.top = 0;
		mWorldView.setCenter(mSpawnPosition);
	}

	//Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If player touches borders, flip its X velocity
	if (position.x <= mWorldBounds.left + 150.f
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	// Apply movements
	for (auto& it : mMaps) {
		it.mSceneGraph.update(deltaTime);
	}
}

void GWORLD::buildMaps() {
	for (int i = 0; i < 3; ++i) {
		mMaps.push_front(GMAP());
	}
}

void GWORLD::draw() {
	mWindow.setView(mWorldView);
	for (auto& it : mMaps) {
		mWindow.draw(it.mSceneGraph);
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